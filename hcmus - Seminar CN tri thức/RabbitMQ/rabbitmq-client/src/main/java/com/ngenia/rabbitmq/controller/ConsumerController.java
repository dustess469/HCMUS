package com.ngenia.rabbitmq.controller;

import com.ngenia.rabbitmq.service.MessageConsumer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@CrossOrigin(origins = "*")
public class ConsumerController {

    @Autowired
    private MessageConsumer messageConsumer;

    @RequestMapping(value = "/getConsumptionInfo", method = RequestMethod.GET, produces = "application/json")
    public String getConsumptionInfo() {
        return "{\n" +
                "\"server\": \"" + messageConsumer.getServer() + "\",\n" +
                "\"nbConsumedMessagesPerSecond\": " + messageConsumer.getNbConsumedMessagesPerSecond() + ",\n" +
                "\"nbTotalConsumedMessages\": " + messageConsumer.getTotalNbConsumedMessages() +
                "\n}";
    }
}