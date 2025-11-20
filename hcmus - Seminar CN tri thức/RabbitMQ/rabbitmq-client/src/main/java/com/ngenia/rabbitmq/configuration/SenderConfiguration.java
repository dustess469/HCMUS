package com.ngenia.rabbitmq.configuration;

//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;
//import org.springframework.amqp.core.AcknowledgeMode;
import org.springframework.amqp.core.Exchange;
import org.springframework.amqp.core.Queue;
//import org.springframework.amqp.rabbit.config.SimpleRabbitListenerContainerFactory;
//import org.springframework.amqp.rabbit.connection.ConnectionFactory;
//import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.Collection;
import java.util.Map;

@Configuration
public class SenderConfiguration {

    //private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @Value("${spring.rabbitmq.sender.exchange}")
    private String exchange;

    @Value("${spring.rabbitmq.sender.routingKey}")
    private String routingKey;

    @Bean
    public Exchange exchange() {
        return new Exchange() {
            @Override
            public String getName() {
                return exchange;
            }

            @Override
            public String getType() {
                return null;
            }

            @Override
            public boolean isDurable() {
                return false;
            }

            @Override
            public boolean isAutoDelete() {
                return false;
            }

            @Override
            public Map<String, Object> getArguments() {
                return null;
            }

            @Override
            public boolean isDelayed() {
                return false;
            }

            @Override
            public boolean isInternal() {
                return false;
            }

            @Override
            public boolean shouldDeclare() {
                return false;
            }

            @Override
            public Collection<?> getDeclaringAdmins() {
                return null;
            }

            @Override
            public boolean isIgnoreDeclarationExceptions() {
                return false;
            }
        };
    }

    @Bean
    public Queue queue() {
        return new Queue(routingKey, true);
    }

}