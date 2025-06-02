# CREW Video Router

A simple Input/Outputs routing system in UE for a Blackmagic video router. It can send **one input** to **multiple outputs**. The input sent will overwrite what's on the outputs. Older inputs sent will stay the same as long as they are not overwritten. You can control everything from the server.
***

Requirements:
- Unreal Engine 5.3
- [Download](https://github.com/CREW-Brussels/CREWVideoRouter) the plugin's folder in the Plugins folder of your project here or if your project is on git, add this command in the Plugins folder of your project:
```
git add submodule https://github.com/CREW-Brussels/CREWVideoRouter.git
```
***

## Use the Plugin in Unreal Engine

1. Create a Blueprint that will be dropped in your scene
2. Create the following node and decide on what is the input and what is the condition depending on what you use the plugin for.
![Screenshot 2025-05-28 143522](https://github.com/user-attachments/assets/8ff0a98f-46fd-4a40-a01c-1bc0f5325fc1)


## About
<img src="https://github.com/user-attachments/assets/bc9dba6e-2478-4d09-86ca-c735ae73f21b" alt="CREW-LOGO" height="70"/>  


    
<img src="https://emil-xr.eu/wp-content/uploads/2022/10/logo_emil-272x300.png)" alt="EMIL-XR-LOGO" height="100"/>
CREW Video Router is being developed by [CREW](http://crew.brussels) as part of [EMIL](https://emil-xr.eu/), the European Media and Immersion Lab, an Innovation Action funded by the European Union and co-funded by Innovate UK. 

## Funding
<img src="https://emil-xr.eu/wp-content/uploads/2022/10/EN-Funded-by-the-EU-POS-1024x215.png)" alt="EU" height="100"/>
This project has received funding from the European Union's Horizon Europe Research and Innovation Programme under Grant Agreement No 101070533 EMIL.
