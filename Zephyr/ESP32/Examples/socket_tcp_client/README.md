# Cliente TCP

En este ejemplo el esp32 se conecta a la red wifi, solicita una ip a través del dhcp para finalmente conectarse
a un servicio 

## ¿Cómo reproducir este ejemplo?

1. Se requiere inicar el server, para lo cual deberá construir el servicio que se encuentra en `tcp_linux_server/`
para luego lanzarlo en la terminal, siga las instrucciones que encuentra en el README.md de ese directorio.

2. Deberá construir el firmware para el esp32, para lo cual modifique los siguientes datos en el prj.conf

## Comando útiles

* Consultar la ip asociada al esp32 desde el PC

```bash
sudo arp-scan --localnet
```

* Consultar la ip desde la uart-shell de zephyr os en el esp32

```bash
net iface
```

