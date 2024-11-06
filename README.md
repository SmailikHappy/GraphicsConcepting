## General

This project introduces wet spots from rain VFX

https://github.com/user-attachments/assets/7670a075-07bb-450e-970f-47c56ade4d48

## Project

The idea was to create a realistic surface response to the VFX. This involved generating a screen-space mask that highlights wet areas, which is then sampled in materials using screen UV coordinates of the pixel currently being rendered.

## Components

The source code contains a module (`/Source/SceneViewExtModule`), that is based on [scene view extension](https://dev.epicgames.com/community/learning/knowledge-base/0ql6/unreal-engine-using-sceneviewextension-to-extend-the-rendering-system) feature of Unreal.\

## Setup for your project
1. Copy the module's folder (`/Source/SceneViewExtModule`) and paste it in their own project's source folder
2. Add the shown code line to the files\
   `/Source/<project name>.Target.cs` & `/Source/<project name>Editor.Target.cs`
```cpp
ExtraModuleNames.Add("SceneViewExtModule");
```
3. In the file `<project name>.uproject` add this to the module list
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

1. Create an instance `RainDropOperater` & call `CreateRainDropExtension()` function and assign the output render target\
   *Ouutput RT will be used in materials*\
   <img src="https://github.com/user-attachments/assets/a67cebe0-e11c-438e-a3e8-0905fdaad9e9">
2. Export relevant to data from the system and send it to the blueprint\
   *It is a rain drop position in our case*\
   <img src="https://github.com/user-attachments/assets/2979dcbc-c777-4343-b303-71822d49a7e5">
3. Receive and put the data into arrays of `RainDropOperator` object\
   <img src="https://github.com/user-attachments/assets/d094033e-44ea-4d93-9bba-8d8da1f4cc3c">
4. Use the mask in materials\
   <img src="https://github.com/user-attachments/assets/7e24bc85-1015-4a09-b1ea-fe8302683623">
