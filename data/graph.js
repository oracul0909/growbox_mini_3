var temp_inside_array = [];
var temp_outside_array = [];
var hum_inside_array = [];
var hum_outside_array = [];
var ground_hum_array = [];

$(document).ready(function () { });

setInterval(function () { }, 2000);

//заполняет весь массив одним значением
function array_start_fill(array, value) {
    for (i = 0; i < 11; i++) {
        array.push(value);
    }
}

//сдвигает все значения массива и добавляет одно в конец
function array_update(array, value) {
    array.shift();
    array.push(value);
}


//заполняет массивы для графиков стартовым значением
function data_array_init() {
    array_start_fill(temp_inside_array, DATA_TEMPERATURE_INSIDE);
    array_start_fill(temp_outside_array, DATA_TEMPERATURE_OUTSIDE);
    array_start_fill(hum_inside_array, DATA_HUMIDITY_INSIDE);
    array_start_fill(hum_outside_array, DATA_HUMIDITY_OUTSIDE);
    array_start_fill(ground_hum_array, DATA_GROUND_HUMIDITY);
}

//сдвигает массив
function data_array_shift() {
    array_update(temp_inside_array, DATA_TEMPERATURE_INSIDE);
    array_update(temp_outside_array, DATA_TEMPERATURE_OUTSIDE);
    array_update(hum_inside_array, DATA_HUMIDITY_INSIDE);
    array_update(hum_outside_array, DATA_HUMIDITY_OUTSIDE);
    array_update(ground_hum_array, DATA_GROUND_HUMIDITY);
}


function draw_graf_1() {

    var d1 = [],
        d2 = [],
        d3 = [],
        d4 = [],
        i, graph;

    for (i = 0; i < 11; i++) {
        d1.push([i, temp_inside_array[i]]);     //температура внутри
        d2.push([i, temp_outside_array[i]]);    //температура снаружи
    }

    for (i = 0; i < 11; i += 10) {
        d3.push([i, DATA_TEMPERATURE_INSIDE_DAY]);       //температура максимум
        d4.push([i, DATA_TEMPERATURE_INSIDE_NIGHT]);     //температура минимум
    }

    // Draw Graph
    graph = Flotr.draw(graphic_1_container, [d1, d2, d3, d4], {

        xaxis: {
            title: "Время, мин",
            minorTickFreq: 2,
            min: 0,
            max: 10
        },
        yaxis: {
            title: "Температура<br>воздуха, °С",
            minorTickFreq: 2,
            min: 0,
            max: 50
        },
        grid: {
            minorVerticalLines: true,
            minorHorizontalLines: true
        }
    });
}


function draw_graf_2() {

    var d5 = [],
        d6 = [],
        d7 = [],
        d8 = [],
        i, graph;
    
    for (i = 0; i < 11; i++) {
        d5.push([i, hum_inside_array[i]]);       //влажность воздуха внутри
        d6.push([i, hum_outside_array[i]]);      //влажность воздуха снаружи
    }

    for (i = 0; i < 11; i += 10) {
        d7.push([i, DATA_HUMIDITY_INSIDE_DAY]);      //влажность воздуха день
        d8.push([i, DATA_HUMIDITY_INSIDE_NIGHT]);    //влажность воздуха ночь
    }

    // Draw Graph
    graph = Flotr.draw(graphic_2_container, [d5, d6, d7, d8], {

        xaxis: {
            title: "Время, мин",
            minorTickFreq: 2,
            min: 0,
            max: 10
        },
        yaxis: {
            title: "Влажность<br>воздуха, %",
            minorTickFreq: 2,
            min: 0,
            max: 100
        },
        grid: {
            minorVerticalLines: true,
            minorHorizontalLines: true
        }
    });
}


function draw_graf_3() {

    var d9 = [],
        d10 = [],
        d11 = [],
        i, graph;

    //влажность почвы
    for (i = 0; i < 11; i++) {
        d9.push([i, ground_hum_array[i]]);
    }

    //влажность почвы максимум
    for (i = 0; i < 11; i += 10) {
        d10.push([i, DATA_GROUND_HUMIDITY_MIN]);
    }

    //влажность почвы минимум
    for (i = 0; i < 11; i += 10) {
        d11.push([i, DATA_GROUND_HUMIDITY_MAX]);
    }

    // Draw Graph
    graph = Flotr.draw(graphic_3_container, [d9, d10, d11], {

        xaxis: {
            title: "Время, мин",
            minorTickFreq: 2,
            min: 0,
            max: 10
        },
        yaxis: {
            title: "Влажность<br>почвы, %",
            minorTickFreq: 2,
            min: 0,
            max: 100
        },
        grid: {
            minorVerticalLines: true,
            minorHorizontalLines: true
        }
    });
}
