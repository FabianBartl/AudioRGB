
# AudioRGB

## Arduino Pin Configuration

| Pin  | Mode            | Label     | Component    | Data            |
| ---: | :-------------- | :-------- | :----------- | :-------------- |
|  $6$ | `output`        | `LED_L_R` | LED left     | red             |
|  $5$ | `output`        | `LED_L_G` | LED left     | green           |
|  $3$ | `output`        | `LED_L_B` | LED left     | blue            |
|      |                 |           |              |                 |
| $11$ | `output`        | `LED_R_R` | LED right    | red             |
| $10$ | `output`        | `LED_R_G` | LED right    | green           |
|  $9$ | `output`        | `LED_R_B` | LED right    | blue            |
|      |                 |           |              |                 |
|  $2$ | `input pull-up` | `TCH_1`   | touch pad    | pad 1           |
|  $4$ | `input pull-up` | `TCH_2`   | touch pad    | pad 2           |
|  $7$ | `input pull-up` | `TCH_3`   | touch pad    | pad 3           |
|  $8$ | `input pull-up` | `TCH_4`   | touch pad    | pad 4           |
|      |                 |           |              |                 |
| $A0$ | `input pull-up` | `AUX_L`   | analog audio | left channel    |
| $A1$ | `input pull-up` | `AUX_R`   | analog audio | right channel   |
|      |                 |           |              |                 |
| $A2$ | `input`         | `RNG_1`   | *nothing*    | *floating-bits* |
| $A3$ | `input`         | `RNG_2`   | *nothing*    | *floating-bits* |

## Nucleo-64 Pin Configuration

![](img/nucleo-64-pin-configuration.png)

| Pin Name | GPIO mode       | GPIO Pull-up/-down | User Label | Component    | Data            |
| :------- | :-------------- | :----------------- | :--------- | :----------- | :-------------- |
| `PB10`   | `analog output` | *none*             | `LED_L_R`  | LED left     | red             |
| `PB4`    | `analog output` | *none*             | `LED_L_G`  | LED left     | green           |
| `PB1`    | `analog output` | *none*             | `LED_L_B`  | LED left     | blue            |
|          |                 |                    |            |              |                 |
| `PA7`    | `analog output` | *none*             | `LED_R_R`  | LED right    | red             |
| `PB6`    | `analog output` | *none*             | `LED_R_G`  | LED right    | green           |
| `PC7`    | `analog output` | *none*             | `LED_R_B`  | LED right    | blue            |
|          |                 |                    |            |              |                 |
| `PA7`    | `digital input` | `Pull-down`        | `TCH_1`    | touch pad    | pad 1           |
| `PB6`    | `digital input` | `Pull-down`        | `TCH_2`    | touch pad    | pad 2           |
| `PC7`    | `digital input` | `Pull-down`        | `TCH_3`    | touch pad    | pad 3           |
| `PC7`    | `digital input` | `Pull-down`        | `TCH_4`    | touch pad    | pad 4           |
|          |                 |                    |            |              |                 |
| `PC13`   | `digital input` | `Pull-down`        | `B1`       | blue button  | on-board button |
|          |                 |                    |            |              |                 |
| `PA1`    | `analog input`  | *none*             | `AUX_L`    | analog audio | left channel    |
| `PA4`    | `analog input`  | *none*             | `AUX_R`    | analog audio | right channel   |
|          |                 |                    |            |              |                 |
| `PC2`    | `analog input`  | *none*             | `RNG_1`    | *nothing*    | *floating-bits* |
| `PC4`    | `analog input`  | *none*             | `RNG_2`    | *nothing*    | *floating-bits* |


## Results

**[Random walk](https://en.wikipedia.org/wiki/Random_walk) by reading analog floating bits from pin $A2$**

![](img/random-walk-by-reading-analog-floating-bits.png)

| Graph | Data        |
| :---- | :---------- |
| blue  | random walk |

***

**Fade random color in / out while playing music**

![](img/fade-random-color-in-out.png)

| Graph  | Data           | Value      |
| :----- | :------------- | :--------- |
| yellow | audio          | volume     |
| purple | filtered audio | volume     |
|        |                |            |
| red    | red value      | brightness |
| green  | green value    | brightness |
| blue   | blue value     | brightness |
