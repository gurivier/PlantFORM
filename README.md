
# PlantFORM

**PlantFORM** [1] is a shape changing user interface that ressemble a plant, which can dynamically unfurl cardboard-and-paper-made leaves through stepper motors, endless screws, and springs and cables. The source codes of the driver and the microcontroller are provided for Arduino Nano and Raspberry Pi.

[1] Élodie Bouzekri and Guillaume Rivière. 2026. Shaping Plant-Like Shape-Changing Interfaces as Vertical Charts: Maximizing Readability, Aesthetics, and Naturalness. arXiv.org, Cornell University, Ithaca, NY, USA, 31 pages (April 2026). DOI: https://doi.org/10.48550/arXiv.2604.15902

## Author

Guillaume Rivière, [ESTIA](https://www.estia.fr), France. ([@gurivier](https://github.com/gurivier/))

## License

Source code is released under the [MIT](https://choosealicense.com/licenses/mit/) license.

Documentation is released under the [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) license.

## Versions' History

* 0.9.3 (2026-10-09)
  * Fix LEDs' blinking control
  * Update Shell scripts
* 0.9.2 (2026-09-24)
  * Integration of EnergySHAPE into the C++ Arduino driver
* 0.9.1 (2026-09-19): First publication
  * This first publication includes:
     * `src/`:
       * The Python controller that receives instructions from MQTT or from prompt
       * The C++ Arduino driver that controls branches' furling and trunk LED's lightning
       * A backup of shell scripts for test procedures

---
[![CC BY-SA 4.0](doc/img/by-sa.png)](https://creativecommons.org/licenses/by-sa/4.0/) Guillaume Rivière, 2023, 2026, [ESTIA](https://www.estia.fr), France.
