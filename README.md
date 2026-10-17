
# PlantFORM

**PlantFORM** [1] is a shape changing user interface that ressemble a plant, which can dynamically unfurl cardboard-and-paper-made leaves through stepper motors, endless screws, and springs and cables. The source codes of the driver and the microcontroller are provided for Arduino Nano and Raspberry Pi.

[1] Élodie Bouzekri and Guillaume Rivière. 2026. Shaping Plant-Like Shape-Changing Interfaces as Vertical Charts: Maximizing Readability, Aesthetics, and Naturalness. arXiv.org, Cornell University, Ithaca, NY, USA, 31 pages (April 2026). DOI: https://doi.org/10.48550/arXiv.2604.15902

## Author

Guillaume Rivière, [ESTIA](https://www.estia.fr), France. ([@gurivier](https://github.com/gurivier/))

## License

Source code is released under the [MIT](https://choosealicense.com/licenses/mit/) license.

Documentation is released under the [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) license.

## Versions' History

* 0.9.7 (2026-10-16)
  * Manage interruption on failed steps
  * Get prototype name from mac address
  * Define max_positions for plantform1 and plantform2 devices
  * Assisted finding of pmax
* 0.9.6 (2026-10-14)
  * Update the class files of EnergySHAPE
  * Add a splash pattern at start up of EnergySHAPE
  * Refactor the class files of Trunk
  * Handle a file to load and save prompt's history 
  * Refactor DriverPlantFORM.py
* 0.9.5 (2026-10-13)
  * Keep working with the digitalWriteFast library
  * Handle prompt with history and line edition
  * Manage a clean exit that saves leaves' positions to hard drive
  * Load leaves' positions from hard drive when powering on
  * Save leaves' positions to hard drive when powering off
  * Add a test script with the exit command
* 0.9.4 (2026-10-12)
  * A new Trunk class now handles the previous LED strip functions
  * Change the parameters of the variation action (i.e., play and values)
  * Add a test script to send forecasts' updates (comprising JSON formatting)
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
