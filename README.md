# MSI-mystic-light-tool

Open project to implement our own led effects for Mystic Light-enabled MSI products

You may know that MSI has released a [C++ SDK](https://msi.com/Landing/mystic-light-motherboard#extension) (update: I uploaded  [here](https://github.com/SimoDax/MSI-mystic-light-tool/blob/master/Mystic_Light_Software_Development_Kit.pdf) the sdk reference since the link on MSI's own website is broken) to embed led control in third-parties applications. As the official Gaming App doesn't support many effects (and in my case, I'm limited to 7 colors), I'm planning to code a customizable led tool to get the most out of our leds :)

If your system is not compatible with Mystic Light 2, there's a nice alternative which interfaces directly to the hardware and doesn't rely on MSI's stuff: [MSIRGB](https://github.com/ixjf/MSIRGB)

UPDATE: For now there's just a stub on how to use it. You need to run the program as administrator to make it work (thanks jugglincode, see issue #1). It works with Mystic Light 2 compatible systems, I tested with ML1 and I got errors after initializing the sdk, feel free to try tho.
I'm going to build a user friendly program with [Qt](http://qt.io) soon (I think it's the best library to interface C code with an UI), so even people not comfortable with programming can use this.
For reference, here's a link to [Mystic Light 1 installer](http://download.msi.com/uti_exe/Mystic_Light.zip), and another one to [Mystic light 2](http://download.msi.com/uti_exe/Mystic_Light_2.zip). 
I got the library working in Visual Studio 2017, I suggest using that. Remember to compile for x86, the dll won't load in 64 bit applications.
**If you manage to get it working, please let us know, feedback is much appreciated!**


## How it works

If you look at the documentation (which is more a reference than a documentation as there's no hint about what every function does), you'll see that every function (except for `Initialize` and `GetDeviceInfo`) require as input parameters `BSTR type, DWORD index`, which are exactly the elements of the two `SAFEARRAYs` returned by `GetDeviceInfo` (`pDevType` and `pLedCount`).
### About 'type':
The reference says that `pDevType` contains the "defined type of all devices". With this they mean that every element of this array is a string (`BSTR`, to be precise) containing the identifier of each hardware you can control leds of (ex: item #1: motherboard name, item #2: gpu name ...and so on). This way the functions setting the lights know which part of the pc you are referring to.
### About 'index':
The second paramater, `index`, lets the functions know which led (or led area, if they aren't controllable one by one) you want to set the colors of, and again, `pLedCount` will give you the led (or led areas) count for each hardware (ex: item #1: 2 (e.g. mobo may have two led zones), #2: 1 (e.g. gpu may have just one led area) ). This way you know the maximum index you can pass to the functions.


If you're not familiar with Safearrays, here's a MSDN article about them: https://msdn.microsoft.com/en-us/magazine/mt795188.aspx

