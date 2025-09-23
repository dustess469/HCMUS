package com.ngenia.rabbitmq.configuration;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.core.AcknowledgeMode;
import org.springframework.amqp.rabbit.config.SimpleRabbitListenerContainerFactory;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class ConsumerConfiguration {

    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @Autowired
    private ConnectionFactory connectionFactory;

    @Value("${spring.rabbitmq.consumer.listener.concurrency}")
    private int concurrentConsumers;

    @Value("${spring.rabbitmq.consumer.listener.max-concurrency}")
    private int maxConcurrentConsumers;

    @Value("${spring.rabbitmq.consumer.listener.batch-enabled}")
    private boolean batchEnabled;

    @Value("${spring.rabbitmq.consumer.listener.batch-size}")
    private int batchSize;

    @Value("${spring.rabbitmq.consumer.listener.acknowledge-mode}")
    private AcknowledgeMode acknowledgeMode;

    @Bean
    public SimpleRabbitListenerContainerFactory consumerBatchContainerFactory() {

        logger.info("####################################################################################");
        logger.info("#");
        logger.info("# Loading Configs .....");
        logger.info("#");
        logger.info("# BatchListener:           {}", batchEnabled);
        logger.info("# BatchSize:               {}", batchSize);
        logger.info("# ConsumerBatchEnabled:    {}", batchEnabled);
        logger.info("# ConcurrentConsumers:     {}", concurrentConsumers);
        logger.info("# MaxConcurrentConsumers:  {}", maxConcurrentConsumers);
        logger.info("# AcknowledgeMode:         {}", acknowledgeMode);
        logger.info("#");
        logger.info("####################################################################################");

        SimpleRabbitListenerContainerFactory factory = new SimpleRabbitListenerContainerFactory();
        factory.setConnectionFactory(connectionFactory);
        factory.setDefaultRequeueRejected(false);
        factory.setChannelTransacted(true);
        factory.setReceiveTimeout(50L);
        factory.setBatchListener(batchEnabled);
        factory.setBatchSize(batchSize);
        factory.setConsumerBatchEnabled(batchEnabled);
        factory.setConcurrentConsumers(concurrentConsumers);
        factory.setMaxConcurrentConsumers(maxConcurrentConsumers);
        factory.setConsecutiveActiveTrigger(1);
        factory.setAcknowledgeMode(acknowledgeMode);

        return factory;
    }
}