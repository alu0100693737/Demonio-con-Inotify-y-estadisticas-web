# Demonio-con-Inotify-y-estadisticas-web

Proyecto para Asignatura Sistemas Operativos del Master en Ingeniería informática por la ULL


El objetivo es que el demonio escriba en un log todos los eventos que se produzcan en la monitorización de uno o varios directorios.

El demonio debería:

* Lanzarse y detenerse correctamente. > HECHO. 

* Hacer el seguimiento de una o varias carpetas que se le pasen como parámetro. > HECHO

* Mostrar como mínimo todos los eventos se produzcan correspondientes en la tabla colgada en el campusvirtual EventosInotify al primer bloque (de IN_ACCESS a IN_OPEN). > HECHO

* Opcional: No volver a lanzar el demonio si ya está activo. > HECHO
* Opcional: Monitorizar los eventos en todos los subdirectorios de los directorios especificados. > NO HECHO
* Opcional: Si se añaden o borran subdirectorios la monitorización debería actualizarse dinámicamente. > NO HECHO

* El demonio debe enviar un resumen de las estadísticas cada cierto tiempo a un servidor. El servidor muestra por pantalla o almacena en un fichero dicha información. > HECHO por pantalla

* Opcional: Comunicación bidireccional entre el servidor y el cliente.
* Opcional: Varios procesos o demonios cliente que envían información a un servidor > HECHO 1 pid varios monitoreos
* Opcional: Convertir en un demonio el código del servidor  HECHO


MODO DE FUNCIONAMIENTO
-------------------------------------------------------------------------------------
Código en local o cloud9 https://ide.c9.io/alu0100693737/vagrant
ejecutar en la carpeta Sistemas Empotrados el demonio cliente con:

./demonioCliente start

./demonioCliente monitorizar NOMBRE_CARPETA MAS_CARPETAS

./demonioCliente stop

Por defecto, cada 1 min, siempre y cuando se haga una operación pasado ese tiempo, se envia
a un servidor los datos recogidos por localhost, puerto 8888. 
Los datos que no se hayan enviado, se harán cuando ./demonioCliente stop

-------------------------------------------------------------------------------------
Ejecutar el demonio servidor en la carpeta SistemasEmpotrados/Servidor 

./demonioServidor start 8888

./demonioStop

La información que se esta enviando continuamente se almacena en Sistemas Empotrados/estadisticasCliente.txt y se borra al enviarse al servidor

La información que recibe el servidor se almacena en Sistemas Empotrados/Servidor/estadisticasServidor.txt

-------------------------------------------------------------------------------------
Adicionalmente, se ha elaborado una pequeña pag web en nodejs disponible actualmente en local o cloud9. Esta web mostrará un conteo de las operaciones que se han realizado en cada una de las carpetas monitorizadas.

Para ver un ejemplo de uso, solo debe entrarse en https://vagrant-alu0100693737.c9users.io/ e introducir un fichero con nombre: estadisticasServidor.txt. Al coincidir el nombre con lo que se espera, se utilizará el fichero estadisticasServidor.txt que está en la carpeta /web.

Si desea probarse con otros datos, debe descargarse la carpeta y ponerla en un servidor local como wamp. 

* Proyecto desarrollado por Iván García Campos

<img src="https://github.com/alu0100693737/Demonio-con-Inotify-y-estadisticas-web/blob/master/capturaInotify.PNG" width="800">


