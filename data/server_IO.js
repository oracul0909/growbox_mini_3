function getDataFromServer() {
  $.ajax({
    url: '/fromserver.json',
    type: "GET",
    dataType: "json",

    success: function (Tables) {
      //console.log(Tables);
      DATA_TEMPERATURE_INSIDE = Tables.DATA_TEMPERATURE_INSIDE;
      $('#temperature_inside').val(DATA_TEMPERATURE_INSIDE);

      DATA_TEMPERATURE_OUTSIDE = Tables.DATA_TEMPERATURE_OUTSIDE;
      $('#temperature_outside').val(DATA_TEMPERATURE_OUTSIDE);

      DATA_HUMIDITY_INSIDE = Tables.DATA_HUMIDITY_INSIDE;
      $('#humidity_inside').val(DATA_HUMIDITY_INSIDE);

      DATA_HUMIDITY_OUTSIDE = Tables.DATA_HUMIDITY_OUTSIDE;
      $('#humidity_inside').val(DATA_HUMIDITY_OUTSIDE);

      DATA_GROUND_HUMIDITY = Tables.DATA_GROUND_HUMIDITY;
      $('#ground_humidity').val(DATA_GROUND_HUMIDITY);

      DATA_LIGHT_INTENCITY_BORDER = Tables.DATA_LIGHT_INTENCITY_BORDER;
      $('#light_intencity_border').val(DATA_LIGHT_INTENCITY_BORDER);

      DATA_TEMPERATURE_INSIDE_DAY = Tables.DATA_TEMPERATURE_INSIDE_DAY;
      $('#temperature_inside_day').val(DATA_TEMPERATURE_INSIDE_DAY);

      DATA_TEMPERATURE_INSIDE_NIGHT = Tables.DATA_TEMPERATURE_INSIDE_NIGHT;
      $('#temperature_inside_night').val(DATA_TEMPERATURE_INSIDE_NIGHT);

      DATA_HUMIDITY_INSIDE_DAY = Tables.DATA_HUMIDITY_INSIDE_DAY;
      $('#humidity_inside_day').val(DATA_HUMIDITY_INSIDE_DAY);

      DATA_HUMIDITY_INSIDE_NIGHT = Tables.DATA_HUMIDITY_INSIDE_NIGHT;
      $('#humidity_inside_night').val(DATA_HUMIDITY_INSIDE_NIGHT);

      DATA_GROUND_HUMIDITY_MAX = Tables.DATA_GROUND_HUMIDITY_MAX;
      $('#ground_humidity_max').val(DATA_GROUND_HUMIDITY_MAX);

      DATA_GROUND_HUMIDITY_MIN = Tables.DATA_GROUND_HUMIDITY_MIN;
      $('#ground_humidity_min').val(DATA_GROUND_HUMIDITY_MIN);

      DATA_ONLY_ONE_LIGHT = Tables.DATA_ONLY_ONE_LIGHT;
      if (DATA_ONLY_ONE_LIGHT == 1) { document.getElementById("only_one_light").checked = true; }
      if (DATA_ONLY_ONE_LIGHT == 0) { document.getElementById("only_one_light").checked = false; }

      DATA_WHITE_FORCIBLY_STOP = Tables.DATA_WHITE_FORCIBLY_STOP;
      if (DATA_WHITE_FORCIBLY_STOP == 1) { document.getElementById("white_forcibly_stop").checked = true; }
      if (DATA_WHITE_FORCIBLY_STOP == 0) { document.getElementById("white_forcibly_stop").checked = false; }

      DATA_FITO_FORCIBLY_STOP = Tables.DATA_FITO_FORCIBLY_STOP;
      if (DATA_FITO_FORCIBLY_STOP == 1) { document.getElementById("fito_forcibly_stop").checked = true; }
      if (DATA_FITO_FORCIBLY_STOP == 0) { document.getElementById("fito_forcibly_stop").checked = false; }

      DATA_WATER_FORCIBLY_STOP = Tables.DATA_WATER_FORCIBLY_STOP;
      if (DATA_WATER_FORCIBLY_STOP == 1) { document.getElementById("water_forcibly_stop").checked = true; }
      if (DATA_WATER_FORCIBLY_STOP == 0) { document.getElementById("water_forcibly_stop").checked = false; }

      DATA_WATER_PUMP_STATUS = Tables.DATA_WATER_PUMP_STATUS;
      if (DATA_WATER_PUMP_STATUS == 1) { document.getElementById("water_pump_status").className = "indicator_green";}
      if (DATA_WATER_PUMP_STATUS == 0) { document.getElementById("water_pump_status").className = "indicator_red";}

      DATA_FITO_LIGHT_STATUS = Tables.DATA_FITO_LIGHT_STATUS;
      if (DATA_FITO_LIGHT_STATUS == 1) { document.getElementById("fito_light_status").className = "indicator_green";}
      if (DATA_FITO_LIGHT_STATUS == 0) { document.getElementById("fito_light_status").className = "indicator_red";}

      DATA_WHITE_LIGHT_STATUS = Tables.DATA_WHITE_LIGHT_STATUS;
      if (DATA_WHITE_LIGHT_STATUS == 1) { document.getElementById("white_light_status").className = "indicator_green";}
      if (DATA_WHITE_LIGHT_STATUS == 0) { document.getElementById("white_light_status").className = "indicator_red";}
    }
  });
}


setInterval(function() {
  //getDataFromServer();
}, 1000);


$(document).ready(function () {
  //getDataFromServer();
});


function setDataOnServer() {
  $.post(
    "/onserver.php",
    {
      b8:  DATA_TEMPERATURE_INSIDE_DAY,
      b9:  DATA_TEMPERATURE_INSIDE_NIGHT,
      b3:  DATA_HUMIDITY_INSIDE_DAY,
      b4:  DATA_HUMIDITY_INSIDE_NIGHT,
      b5:  DATA_GROUND_HUMIDITY_MAX,
      b6:  DATA_GROUND_HUMIDITY_MIN,
      b7:  DATA_WATER_FORCIBLY_STOP,
      b12: DATA_FITO_FORCIBLY_STOP,
      b13: DATA_ONLY_ONE_LIGHT,
      b14: DATA_LIGHT_INTENCITY_BORDER,
      b15: DATA_WHITE_FORCIBLY_STOP
    },
  );
  console.log(DATA_ONLY_ONE_LIGHT);
}


/*
function onAjaxSuccess(data) {}

State = false;
function onAjaxSuccess2(data) {
  State = true;
}

var Begin = false;
$(document).ready(function () {
      setTimeout(function () {
        if (Begin == false) {
          GetFlameState();
        }
      }, 1000);
});

function GetFlameState() {
  nocache = "&nocache=" + Math.random() * 1000000;
  var request = new XMLHttpRequest();
  request.onreadystatechange = function () {
    if (this.readyState == 4) {
      if (this.status == 200) {
        if (this.responseText != null) {
          var arrayOfStrings = this.responseText.split(":");

          $('#Temp_I').text(arrayOfStrings[0]);
          $('#Temp_O').text(arrayOfStrings[1]);
          $('#HUM_I').text(arrayOfStrings[6]);
          $('#HUM_O').text(arrayOfStrings[7]);
          $('#HUM_T').text(arrayOfStrings[3]);
          $('#LIGHT_T').text(arrayOfStrings[8]);

          if (v_auto_t == "on") {
            if (arrayOfStrings[15] == "on") { document.getElementById("went_1").checked = true; }
            if (arrayOfStrings[15] == "off") { document.getElementById("went_1").checked = false; }

            if (arrayOfStrings[14] == "on") { document.getElementById("furn").checked = true; }
            if (arrayOfStrings[14] == "off") { document.getElementById("furn").checked = false; }

            if (arrayOfStrings[16] == "open") { document.getElementById("win1").checked = true; }
            if (arrayOfStrings[16] == "close") { document.getElementById("win1").checked = false; }

            if (arrayOfStrings[17] == "open") { document.getElementById("win2").checked = true; }
            if (arrayOfStrings[17] == "close") { document.getElementById("win2").checked = false; }

            if (arrayOfStrings[18] == "on") { document.getElementById("went_2").checked = true; }
            if (arrayOfStrings[18] == "off") { document.getElementById("went_2").checked = false; }
          }
          if (v_auto_h_i == "on") {
            if (arrayOfStrings[16] == "open") { document.getElementById("win1").checked = true; }
            if (arrayOfStrings[16] == "close") { document.getElementById("win1").checked = false; }

            if (arrayOfStrings[17] == "open") { document.getElementById("win2").checked = true; }
            if (arrayOfStrings[17] == "close") { document.getElementById("win2").checked = false; }

            if (arrayOfStrings[18] == "on") { document.getElementById("went_2").checked = true; }
            if (arrayOfStrings[18] == "off") { document.getElementById("went_2").checked = false; }
          }
          if (v_auto_l == "on") {
            if (arrayOfStrings[19] == "on") { document.getElementById("light").checked = true; }
            if (arrayOfStrings[19] == "off") { document.getElementById("light").checked = false; }
          }
          if (v_auto_h == "on") {
            if (arrayOfStrings[20] == "on") { document.getElementById("water").checked = true; }
            if (arrayOfStrings[20] == "off") { document.getElementById("water").checked = false; }
          }
        }
      }
    }
  }
  // request.open("GET", "ajax_flame" + nocache, true);
  // request.send(null);
  setTimeout('GetFlameState()', 5000);
}
*/