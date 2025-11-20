package com.ngenia.rabbitmq.controller;

import com.ngenia.rabbitmq.service.MessageSender;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin(origins = "*")
public class SenderController {

    @Autowired
    private MessageSender messageSender;

    @RequestMapping(value = "/send", method = RequestMethod.GET, produces = "application/json")
    public String send(@RequestParam("message") String message) {
        messageSender.send(message);
        return "{\"status\": \"sent\"}";
    }
}