function temp_day_plus() {
  if (DATA_TEMPERATURE_INSIDE_DAY >= 0 && DATA_TEMPERATURE_INSIDE_DAY < 50) DATA_TEMPERATURE_INSIDE_DAY++;
  $('#temperature_inside_day').val(DATA_TEMPERATURE_INSIDE_DAY);
  draw_graf_1();
  setDataOnServer();
};

function temp_day_minus() {
  if (DATA_TEMPERATURE_INSIDE_DAY > 0 && DATA_TEMPERATURE_INSIDE_DAY <= 50) DATA_TEMPERATURE_INSIDE_DAY--;
  $('#temperature_inside_day').val(DATA_TEMPERATURE_INSIDE_DAY);
  draw_graf_1();
  setDataOnServer();
};

function temp_night_plus() {
  if (DATA_TEMPERATURE_INSIDE_NIGHT >= 0 && DATA_TEMPERATURE_INSIDE_NIGHT < 50) DATA_TEMPERATURE_INSIDE_NIGHT++;
  $('#temperature_inside_night').val(DATA_TEMPERATURE_INSIDE_NIGHT);
  draw_graf_1();
  setDataOnServer();
};

function temp_night_minus() {
  if (DATA_TEMPERATURE_INSIDE_NIGHT > 0 && DATA_TEMPERATURE_INSIDE_NIGHT <= 50) DATA_TEMPERATURE_INSIDE_NIGHT--;
  $('#temperature_inside_night').val(DATA_TEMPERATURE_INSIDE_NIGHT);
  draw_graf_1();
  setDataOnServer();
};

function hum_day_plus() {
  if (DATA_HUMIDITY_INSIDE_DAY >= 0 && DATA_HUMIDITY_INSIDE_DAY < 100) DATA_HUMIDITY_INSIDE_DAY++;
  $('#humidity_inside_day').val(DATA_HUMIDITY_INSIDE_DAY);
  draw_graf_2();
  setDataOnServer();
};

function hum_day_minus() {
  if (DATA_HUMIDITY_INSIDE_DAY > 0 && DATA_HUMIDITY_INSIDE_DAY <= 100) DATA_HUMIDITY_INSIDE_DAY--;
  $('#humidity_inside_day').val(DATA_HUMIDITY_INSIDE_DAY);
  draw_graf_2();
  setDataOnServer();
};

function hum_night_plus() {
  if (DATA_HUMIDITY_INSIDE_NIGHT >= 0 && DATA_HUMIDITY_INSIDE_NIGHT < 100) DATA_HUMIDITY_INSIDE_NIGHT++;
  $('#humidity_inside_night').val(DATA_HUMIDITY_INSIDE_NIGHT);
  draw_graf_2();
  setDataOnServer();
};

function hum_night_minus() {
  if (DATA_HUMIDITY_INSIDE_NIGHT > 0 && DATA_HUMIDITY_INSIDE_NIGHT <= 100) DATA_HUMIDITY_INSIDE_NIGHT--;
  $('#humidity_inside_night').val(DATA_HUMIDITY_INSIDE_NIGHT);
  draw_graf_2();
  setDataOnServer();
};

function ground_max_plus() {
  if (DATA_GROUND_HUMIDITY_MAX >= 0 && DATA_GROUND_HUMIDITY_MAX < 100) DATA_GROUND_HUMIDITY_MAX++;
  $('#ground_humidity_max').val(DATA_GROUND_HUMIDITY_MAX);
  draw_graf_3();
  setDataOnServer();
};

function ground_max_minus() {
  if (DATA_GROUND_HUMIDITY_MAX > 0 && DATA_GROUND_HUMIDITY_MAX <= 100) DATA_GROUND_HUMIDITY_MAX--;
  $('#ground_humidity_max').val(DATA_GROUND_HUMIDITY_MAX);
  draw_graf_3();
  setDataOnServer();
};

function ground_min_plus() {
  if (DATA_GROUND_HUMIDITY_MIN >= 0 && DATA_GROUND_HUMIDITY_MIN < 100) DATA_GROUND_HUMIDITY_MIN++;
  $('#ground_humidity_min').val(DATA_GROUND_HUMIDITY_MIN);
  draw_graf_3();
  setDataOnServer();
};

function ground_min_minus() {
  if (DATA_GROUND_HUMIDITY_MIN > 0 && DATA_GROUND_HUMIDITY_MIN <= 100) DATA_GROUND_HUMIDITY_MIN--;
  $('#ground_humidity_min').val(DATA_GROUND_HUMIDITY_MIN);
  draw_graf_3();
  setDataOnServer();
};

function light_intencity_plus() {
  if (DATA_LIGHT_INTENCITY_BORDER >= 0 && DATA_LIGHT_INTENCITY_BORDER < 5000) DATA_LIGHT_INTENCITY_BORDER += 100;
  $('#light_intencity_border').val(DATA_LIGHT_INTENCITY_BORDER);
  setDataOnServer();
};

function light_intencity_minus() {
  if (DATA_LIGHT_INTENCITY_BORDER > 0 && DATA_LIGHT_INTENCITY_BORDER <= 5000) DATA_LIGHT_INTENCITY_BORDER -= 100;
  $('#light_intencity_border').val(DATA_LIGHT_INTENCITY_BORDER);
  setDataOnServer();
};


function only_one_light_switch() {
  switch (DATA_ONLY_ONE_LIGHT) {
    case 0:
      document.getElementById("only_one_light").checked = true;
      DATA_ONLY_ONE_LIGHT = 1;
      break;
    case 1:
      document.getElementById("only_one_light").checked = false;
      DATA_ONLY_ONE_LIGHT = 0;
      break;
  }
  setDataOnServer();
}


function white_switch() {
  switch (DATA_WHITE_FORCIBLY_STOP) {
    case 0:
      document.getElementById("white_forcibly_stop").checked = true;
      DATA_WHITE_FORCIBLY_STOP = 1;
      break;
    case 1:
      document.getElementById("white_forcibly_stop").checked = false;
      DATA_WHITE_FORCIBLY_STOP = 0;
      break;
  }
  setDataOnServer();
}


function fito_switch() {
  switch (DATA_FITO_FORCIBLY_STOP) {
    case 0:
      document.getElementById("fito_forcibly_stop").checked = true;
      DATA_FITO_FORCIBLY_STOP = 1;
      break;
    case 1:
      document.getElementById("fito_forcibly_stop").checked = false;
      DATA_FITO_FORCIBLY_STOP = 0;
      break;
  }
  setDataOnServer();
}


function water_switch() {
  switch (DATA_WATER_FORCIBLY_STOP) {
    case 0:
      document.getElementById("water_forcibly_stop").checked = true;
      DATA_WATER_FORCIBLY_STOP = 1;
      break;
    case 1:
      document.getElementById("water_forcibly_stop").checked = false;
      DATA_WATER_FORCIBLY_STOP = 0;
      break;
  }
  setDataOnServer();
}