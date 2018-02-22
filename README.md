# Demonio-con-Inotify-y-estadisticas-web

Proyecto para Asignatura Sistemas Operativos del Master en Ingeniería informática por la ULL


El objetivo es que el demonio escriba en un log todos los eventos que se produzcan en la monitorización de uno o varios directorios.

El demonio debería:

* Lanzarse y detenerse correctamente. HECHO. Solo una ejecucion a la vez

* Hacer el seguimiento de una o varias carpetas que se le pasen como parámetro.

* Mostrar como mínimo todos los eventos se produzcan correspondientes en la tabla colgada en el campusvirtual EventosInotify al primer bloque (de IN_ACCESS a IN_OPEN).

* Opcional: No volver a lanzar el demonio si ya está activo. HECHO
* Opcional: Monitorizar los eventos en todos los subdirectorios de los directorios especificados.
* Opcional: Si se añaden o borran subdirectorios la monitorización debería actualizarse dinámicamente. 

* El demonio debe enviar un resumen de las estadísticas cada cierto tiempo a un servidor. El servidor muestra por pantalla o almacena en un fichero dicha información. 

* Opcional: Comunicación bidireccional entre el servidor y el cliente.
* Opcional: Varios procesos o demonios cliente que envían información a un servidor
* Opcional: Convertir en un demonio el código del servidor  
