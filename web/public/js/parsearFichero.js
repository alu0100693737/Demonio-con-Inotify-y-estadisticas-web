//Poner contenido fichero
function readSingleFile(e) {
  
  console.log("entrando\n");
  var file = e.target.files[0];
  if (!file)
  return;

  var reader = new FileReader();
  reader.onload = function(e) {
    var contents = e.target.result;
    displayContents(contents);
  };
  reader.readAsText(file);

  var input = document.getElementById("file-input");
  var file = input.value.split("\\");
  var fileName = file[file.length-1];
  console.log("ASCO " + fileName);
  //Actualizamos las tablas de estadisticas actuales
  leerFicheroEstadisticas(fileName);
}


function displayContents(contents) {
  var element = document.getElementById('file-content');
  element.textContent = contents;
}

//Nuevo
function leerFicheroEstadisticas(fichero) {
  var rawFile = new XMLHttpRequest();
  var allText;
  console.log("HOLA " + fichero);
  rawFile.open("GET", fichero, false);
  rawFile.onreadystatechange = function ()  {
    if(rawFile.readyState === 4)  {
      if(rawFile.status === 200 || rawFile.status == 0) {
        allText = rawFile.responseText;
        
        var splitear = allText.split("\n")
        filtrarYClasificar(splitear);

        document.getElementById("file-content").innerHTML = allText;
        return;
        console.log("No deberia ocurrir, me salto el return");
      }
    }
  }
  rawFile.send(null);
}

function propiedades() {
  this.nombre = ""; this.create = 0; this.open = 0; this.modify = 0; this.access = 0; this.attrib = 0;
  this.close_write = 0; this.close_nowrite = 0; this.deletefile = 0; this.deletefile_self = 0;
  this.move_self = 0; this.moved_from = 0; this.moved_to = 0; this.open = 0;
  /*nombre:"", create:0, open:0, modify:0, access:0, attrib:0,
  close_write:0, close_nowrite:0, deletefile:0, deletefile_self:0,
  move_self:0, moved_from:0, moved_to:0, open:0*/
}

function filtrarYClasificar(splitear) {
  var carpetas = [];

  console.log("Valor " + splitear.length);
  for(i = 0; i < splitear.length; i++) {
    var palabras = splitear[i].split(" ");
    if(palabras[1] == "Carpeta:") {
      var j;
      var encontrado = false;
      for(j = 0; j < carpetas.length; j++) {
          if(carpetas[j].nombre.trim() == palabras[2].trim()) {
            encontrado = true;
            break;
          }
      }
      if(encontrado == false) {
        var nuevaPropiedad = new propiedades;
        console.log("Intentando anadir la carpeta " + palabras[2]);

        carpetas.push(nuevaPropiedad);
        carpetas[j].nombre = palabras[2].trim();
        console.log("j vale " + j + " " + carpetas[j].nombre);
      }

      var opcion = palabras[3].trim();

      switch(opcion) {

        case "mask=IN_OPEN":
        carpetas[j].open++;
        break;

        case "mask=IN_CREATE":
        carpetas[j].create++;
        break;

        case "mask=IN_MODIFY":
        carpetas[j].modify++;
        break;

        case "mask=IN_ACCESS":
        carpetas[j].access++;
        break;

        case "mask=IN_ATTRIB":
        carpetas[j].attrib++;
        break;

        case "mask=IN_CLOSE_WRITE":
        carpetas[j].close_write++;
        break;

        case "mask=IN_CLOSE_NOWRITE":
        carpetas[j].close_nowrite++;
        break;

        case "mask=IN_DELETE":
        carpetas[j].deletefile++;
        break;

        case "mask=IN_DELETE_SELF":
        carpetas[j].deletefile_self++;
        break;

        case "mask=IN_MOVE_SELF":
        carpetas[j].move_self++;
        break;

        case "cookie":
          if(palabras[6].trim() == "mask=IN_MOVED_FROM")
            carpetas[j].moved_from++;
          else
            console.log("CASO NO CONTEMPLADO ");
          break;

        case "mask=IN_MOVED_TO":
        carpetas[j].moved_to++;
        break;

        default:
        console.log("ERROR!!!! en " + i + " " + opcion);
      }
    }
  }
  /*console.log("Create: " + create);
  console.log("Open: " + open);
  console.log("Modify: " + modify);
  console.log("Access: " + access);
  console.log("Attrib: " + attrib);
  console.log("Close_write: " + close_write);
  console.log("Close_nowrite: " + close_nowrite);
  console.log("Delete: " + deletefile);
  console.log("Delete_self: " + deletefile_self);
  console.log("Move_self: " + move_self);
  console.log("Moved_from: " + moved_from);
  console.log("Moved_to: " + moved_to);*/

  console.log(carpetas);
  mostrarResultado(carpetas);
}

function mostrarResultado(carpetas) {
  var i;
  var contenido = "";
  for(i = 0; i < carpetas.length; i++) {
      if ((i % 2) == 1) {
        contenido += '<table style="display: inline-block;">';
      } else {
        contenido += '<table style="float: left;">';
      }

      contenido += '<tbody><tr><td>  <table class="carpetas"><tr><td><FONT FACE="raro, courier" SIZE=4 COLOR="black">Nombre: ';
      contenido += carpetas[i].nombre.trim();

      contenido += '</FONT></td><td><FONT FACE="raro, courier" SIZE=5 COLOR="black">Num de llamadas</FONT></td></tr><tr><td>IN_CREATE</td><td>';
      contenido += carpetas[i].create;
      contenido += '</td></tr><tr><td>IN_OPEN</td><td>';
      contenido += carpetas[i].open;
      contenido += '</td></tr><tr><td>IN_MODIFY</td><td>';
      contenido += carpetas[i].modify;
      contenido += '</td></tr><tr><td>IN_ACCESS</td><td>';
      contenido += carpetas[i].access;
      contenido += '</td></tr><tr><td>IN_ATTRIB</td><td>';
      contenido += carpetas[i].attrib;
      contenido += '</td></tr><tr><td>IN_CLOSE_WRITE</td><td>'
      contenido += carpetas[i].close_write;
      contenido += '</td></tr><tr><td>IN_CLOSE_NOWRITE</td><td>';
      contenido += carpetas[i].close_nowrite;
      contenido += '</td></tr><tr><td>IN_DELETE</td><td>';
      contenido += carpetas[i].deletefile;
      contenido += '</td></tr><tr><td>IN_DELETE_SELF</td><td>';
      contenido += carpetas[i].deletefile_self;
      contenido += '</td></tr><tr><td>IN_MOVE_SELF</td><td>';
      contenido += carpetas[i].move_self;
      contenido += '</td></tr><tr><td>IN_MOVED_FROM</td><td>';
      contenido += carpetas[i].moved_from;
      contenido += '</td></tr><tr><td>IN_MOVED_TO</td><td>';
      contenido += carpetas[i].moved_to;
      contenido += '</td></tr></table></td></tr></tbody></table>';

  }
  $("#misTablas").html(contenido);
}
