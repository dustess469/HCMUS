package com.ngenia.rabbitmq.service;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Component;

import java.text.DecimalFormat;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;

@Component
public class MessageConsumer {

    Logger logger = LoggerFactory.getLogger(MessageConsumer.class);

    @Value("${spring.rabbitmq.host}")
    private String host;

    private LocalDateTime before = LocalDateTime.now();
    private LocalDateTime now = LocalDateTime.now();

    private static Integer nbConsumedMessages = 0;
    private static Integer totalNbConsumedMessages = 0;

    private Double nbConsumedMessagesPerSecond;
    private static DecimalFormat df1 = new DecimalFormat("#.#");

    public String getServer() {
        return this.host;
    }

    public Integer getTotalNbConsumedMessages() {
        return totalNbConsumedMessages;
    }

    public String getNbConsumedMessagesPerSecond() {
        nbConsumedMessagesPerSecond = nbConsumedMessages / ((double)ChronoUnit.MILLIS.between(before, now = LocalDateTime.now())/1000);
        nbConsumedMessages = 0;
        before = now;
        return df1.format(nbConsumedMessagesPerSecond);
    }

    @RabbitListener(queues = {"#{'${spring.rabbitmq.consumer.queues}'.split(',')}"}, containerFactory = "consumerBatchContainerFactory")
    public void handle(@Payload String message) {
        logger.debug(" + [" + ++nbConsumedMessages + "] messages Received.");
        logger.debug(" = [" + ++totalNbConsumedMessages + "] Total messages Consumed.");
    }
}