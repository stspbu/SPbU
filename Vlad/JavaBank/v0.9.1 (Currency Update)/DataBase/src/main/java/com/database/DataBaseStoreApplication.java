package com.database;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.web.client.RestTemplate;

//spring.datasource.url=jdbc:h2:~/test; DB_CLOSE_ON_EXIT=FALSE
@SpringBootApplication
public class DataBaseStoreApplication {
	public static void main(String[] args) {
        new AnnotationConfigApplicationContext(DataBaseStoreApplicationConfig.class);
		SpringApplication.run(DataBaseStoreApplication.class, args);
	}
	@Bean
	public RestTemplate restTemplate() {
		return new RestTemplate();
	}
}
