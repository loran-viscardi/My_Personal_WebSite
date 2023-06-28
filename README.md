# Site utilizado na disciplina de Sistemas Embarcados
## Os diferentes arquivos contidos nesse repositório foram utilizados para estudar a criação Web, desde páginas simples utilizando HTML e PHP, API's utilizando JSON, até DashBoards para monitoramento remoto, explorando as possibilidades de IoT.

Para obtenção de um Public IP foi utilizada uma instância EC2, rodando OS Linux 20.04, gratuita por 1 ano através da Amazon Web Services (AWS), logo foi instalado um servidor web Apache 2, propiciando uma comunicação HTTP através da porta 80, fazendo o uso de HTML e PHP, foi desenvolvido a primeira página web.
 
 ### http://loranviscardi.duckdns.org
 ![Captura de tela 2023-06-27 225602](https://github.com/loran-viscardi/My_Personal_WebSite/assets/103280132/752c65d3-fb04-4a04-b1ff-ca38bfdcc064)

Juntamente com a criação dessa página foi criada outra página para melhor compreensão das linguagens utilizadas, fazendo uso de CSS e JavaScript, uma pequena apresentação sobre sistemas embarcados foi desenvolvida
### http://loranviscardi.duckdns.org/index.php
![Captura de tela 2023-06-27 230907](https://github.com/loran-viscardi/My_Personal_WebSite/assets/103280132/3b3c299f-f46d-4a4f-9795-79a4296b0da0)

Para o estudo de mensagens JSON foi criada uma API que  é capaz de receber mensagnes em JSON de um projeto da NASA que divulga a cada 24 horas uma imagem e sua explicação, onde o código desenvolvido é capaz de receber essas informações enviadas pela agência e publicar no site, possibilitando que a página seja interativa
### http://loranviscardi.duckdns.org/api-nasa/apod-code
![Captura de tela 2023-06-27 231440](https://github.com/loran-viscardi/My_Personal_WebSite/assets/103280132/726cd556-36a2-44e3-ba79-01eea91e284e)

Utilizando mensagens JSON, foi criado uma página que recebia mensagens JSON, contendo dados de temperatura e umidade de uma sala enviadas através de um MCU ESP32, possibilitando a vizualização desses dados através da web 
### http://loranviscardi.duckdns.org/esp_connect/month.php
![Captura de tela 2023-06-27 232139](https://github.com/loran-viscardi/My_Personal_WebSite/assets/103280132/6b71fcae-1c9f-4722-9f46-ad6a2358d5e3)

Para possibilitar uma integração IoT, instalando uma aplicação Node-RED no Linux, facilitou a criação de dashboards dinâmicas, que recebem dados em tempo real enviados por um ESP32, enviando esses dados a um broker MQTT. Através da aplicação é possível receber esses dados via MQTT e tratá-los devidamente.
### http://loranviscardi.duckdns.org:1880/ui
![Captura de tela 2023-06-21 163752](https://github.com/loran-viscardi/My_Personal_WebSite/assets/103280132/2e6cc1f0-0501-4178-a6be-767eee559d02)
![Captura de tela 2023-06-21 163831](https://github.com/loran-viscardi/My_Personal_WebSite/assets/103280132/09042c7a-0a20-45d3-b4ab-0d242ab059c9)





