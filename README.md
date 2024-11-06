## General

This project introduces wet spots from rain VFX

https://github.com/user-attachments/assets/7670a075-07bb-450e-970f-47c56ade4d48

## Usage

1. Create an instance `RainDropOperater` & call `CreateRainDropExtension()` function and assign the output render target
   ![Initializing](/github_assets/create-extension.png | width = 100)
2. Export relevant to data from the system and send it to the blueprint
   *It is a rain drop position in our case*\
   ![Export data](/github_assets/export-data-from-vfx.png)
3. Receive and put the data into arrays of RainDropOperator object\
   ![Push data to the array](/github_assets/push-data.png)
4. Use the mask in materials\
   ![Use mask in materials](/github_assets/use-mask.png)
   <img src="https://github.com/user-attachments/assets/7e24bc85-1015-4a09-b1ea-fe8302683623" width="20">
