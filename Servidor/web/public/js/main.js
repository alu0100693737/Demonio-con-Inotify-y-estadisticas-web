$(document).ready(init);

function init() {
  "use strict"
    $("#anadirFila").click(function () {
         $("#miTabla").each(function () {
             var tds = '<tr><td>&nbsp</td>';
             /*jQuery.each($('tr:last td', this), function () {
                 tds += '<td>' + $(this).html() + '</td>';
             });*/
             tds += '</tr>';
             if ($('tbody', this).length > 0) {
                 $('tbody', this).append(tds);
             } else {
                 $(this).append(tds);
             }
         });
    });
    document.getElementById('file-input')
  .addEventListener('change', readSingleFile, false);
}
