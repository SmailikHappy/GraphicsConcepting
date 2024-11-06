## General

This project introduces wet spots from rain VFX

https://github.com/user-attachments/assets/7670a075-07bb-450e-970f-47c56ade4d48

## Project

The idea was to create a realistic surface response to the VFX. This involved generating a screen-space mask that highlights wet areas, which is then sampled in materials using screen UV coordinates of the pixel currently being rendered.

## Pipeline explanation

The source code includes a module (`/Source/SceneViewExtModule`) responsible for executing the core algorithm.\
This algorithm leverages Unreal Engine's [Scene View Extension](https://dev.epicgames.com/community/learning/knowledge-base/0ql6/unreal-engine-using-sceneviewextension-to-extend-the-rendering-system) feature to listen for the `PreRenderView_renderThread()` function. Within this function, a custom pass renders a *wetness* screen mask before the base pass *(referred to as **Rain mask pass** in code and debug tools)*, ensuring the mask is available within the same frame.\
In the project, the mask is sampled in material graphs using screen UV coordinates. 


## Setup for your project
1. Copy the module folder (`/Source/SceneViewExtModule`) and paste it into your project's source folder.
2. Add the following code line to both `/Source/<project name>.Target.cs` and `/Source/<project name>Editor.Target.cs`:
```cpp
ExtraModuleNames.Add("SceneViewExtModule");
```
3. In the `<project name>.uproject` file, add this to the module list
```json
{
   "Name": "SceneViewExtModule",
   "Type": "Runtime",
   "LoadingPhase": "PostConfigInit"
}  
```
4. Build the project

Now, you should be able to use `RainDropOperator` class

## Usage

1. Create an instance of `RainDropOperator`, call the `CreateRainDropExtension()` function and assign the output render target.\
   *This output render target (RT) will be referenced in materials.*\
   <img src="https://github.com/user-attachments/assets/a67cebe0-e11c-438e-a3e8-0905fdaad9e9">
2. Export relevant data from the system and send it to the blueprint.\
   *In our case, this is the position of a raindrop*\
   <img src="https://github.com/user-attachments/assets/2979dcbc-c777-4343-b303-71822d49a7e5">
3. Receive the data and store it in the `RainDropOperator` object's arrays.\
   <img src="https://github.com/user-attachments/assets/d094033e-44ea-4d93-9bba-8d8da1f4cc3c">
4. Reference the mask within materials to apply effects.\
   <img src="https://github.com/user-attachments/assets/7e24bc85-1015-4a09-b1ea-fe8302683623">
