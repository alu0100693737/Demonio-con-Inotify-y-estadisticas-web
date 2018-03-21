# Demonio-con-Inotify-y-estadisticas-web

Proyecto para Asignatura Sistemas Operativos del Master en Ingeniería informática por la ULL


El objetivo es que el demonio escriba en un log todos los eventos que se produzcan en la monitorización de uno o varios directorios.

El demonio debería:

* Lanzarse y detenerse correctamente. HECHO. Solo una ejecucion a la vez HECHO

* Hacer el seguimiento de una o varias carpetas que se le pasen como parámetro. HECHO

* Mostrar como mínimo todos los eventos se produzcan correspondientes en la tabla colgada en el campusvirtual EventosInotify al primer bloque (de IN_ACCESS a IN_OPEN). HECHO

* Opcional: No volver a lanzar el demonio si ya está activo. HECHO
* Opcional: Monitorizar los eventos en todos los subdirectorios de los directorios especificados.
* Opcional: Si se añaden o borran subdirectorios la monitorización debería actualizarse dinámicamente. 

* El demonio debe enviar un resumen de las estadísticas cada cierto tiempo a un servidor. El servidor muestra por pantalla o almacena en un fichero dicha información. HECHO por pantalla

* Opcional: Comunicación bidireccional entre el servidor y el cliente.
* Opcional: Varios procesos o demonios cliente que envían información a un servidor HECHO 1 pid varios monitoreos
* Opcional: Convertir en un demonio el código del servidor  HECHO


LEEME

Código en local o cloud9
ejecutar en la carpeta Sistemas Empotrados el demonio cliente con:

./demonioCliente start

./demonioCliente monitorizar NOMBRE_CARPETA

./demonioCliente stop

Por defecto, cada 1 min, siempre y cuando se haga una operación pasado ese tiempo, se envia
a un servidor los datos recogidos por localhost, puerto 8888. 
Los datos que no se hayan enviado, se harán cuando ./demonioCliente stop


Ejecutar el demonio servidor en la carpeta SistemasEmpotrados/Servidor 

./demonioServidor start 8888

./demonioStop

La información que se esta enviando continuamente se almacena en Sistemas Empotrados/estadisticasCliente.txt y se borra al enviarse al servidor

La información que recibe el servidor se almacena en Sistemas Empotrados/Servidor/estadisticasServidor.txt



Adicionalmente, se ha elaborado una pequeña pag web en nodejs disponible actualmente en cloud9. 
Solo debe entrarse en https://vagrant-alu0100693737.c9users.io/ e introducir un fichero con nombre: estadisticasServidor.txt
Se mostrará un conteo de las operaciones que se han realizado en cada una de las carpetas monitorizadas.
FOTO