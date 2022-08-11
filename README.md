# Panel Control
Layer for smbus/I2C interfaces;
- PCF8574 module for quick reading 8-bit data from buttons/encoders;
- SSD1306 module for displaying data:
    - relies on cairo for drawing
    - XML files describes screen layouts
- OSC for dispatching control data;
---
## XML Schemas
At program loading, it will sweep 'schemas' directory and keep parsed XML layouts in memory for quick changing screens and assigning functions to physical controls.  
Encoders will be assigned to XML Nodes in the order they appear.

Available Nodes:
- FolderList
    * args: path, address
    * encoder: browse through folder named in `path`
    * 'OK' button: send file name to `address`
- PresetBroadcast
    * args: preset sub folder
    * encoder: browse through presets on chosen sub folder
    * 'OK' button: send every entry on chosen file via OSC
- TextParameter:
    * args: address, unit, max, min
    * encoder: send message of a value within `min` and `max` via address, displays value+ `unit` onscreen
- Tabs
    * container for `Tab` node, encoder changes view inside each `Tab`
