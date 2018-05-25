# MSI-mystic-light-tool

Open project to implement our own led effects for Mystic Light-enabled MSI products

You may know that MSI has released a [C++ SDK](https://msi.com/Landing/mystic-light-motherboard#extension) to embed led control in third-parties applications. As the official Gaming App doesn't support many effects (and in my case, I'm limited to 7 colors), I'm planning to code a customizable led tool to get the most out of our leds :)

UPDATE: I've actually tested the library. I've posted a stub program on how to use it, but on my pc it always ends up with a Timeout error when I call MLAPI_Initialize(). Maybe you'll have better luck.
For reference, here's a link to [Mystic Light 1 installer](http://download.msi.com/uti_exe/Mystic_Light.zip), and another one to [Mystic light 2](http://download.msi.com/uti_exe/Mystic_Light_2.zip). 
I got the library working in Visual Studio 2017, I suggest using that.
**If you manage to get it working, please let me know either here, by dropping a mail or make a pull request**

## Intuition on how it works

If you look at the documentation (which is more a reference than a documentation as there's no hint about what every function does), you'll see that every function (except for `Initialize` and `GetDeviceInfo`) require as input parameters `BSTR type, DWORD index`, which are exactly the elements of the two `SAFEARRAYs` returned by `GetDeviceInfo` (`pDevType` and `pLedCount`).
### About 'type':
The reference says that `pDevType` contains the "defined type of all devices". I think they mean (again, I couldn't test it but I'm 99% sure it's like this) that every element of this array is a string (`BSTR`, to be precise) containing the identifier of each hardware you can control leds of (ex: item #1: motherboard name, item #2: gpu name ...and so on). This way the functions setting the lights know which part of the pc you are referring to.
### About 'index':
The second paramater, `index`, should let the functions know which led (or led area, if they aren't controllable one by one) you want to set the colors of, and again, `pLedCount` will give you the led (or led areas) count for each hardware (ex: item #1: 2 (e.g. mobo may have two led zones), #2: 1 (e.g. gpu may have just one led area) ). This way you know the maximum index you can pass to the functions.


If you're not familiar with Safearrays, here's a MSDN article about them: https://msdn.microsoft.com/en-us/magazine/mt795188.aspx

This should be the supported hardware list for Mystic Light v1:

MB:
	MS-7991|1.x
	MS-7A15|1.x
	MS-7A44|1.x
	MS-7A49|1.x
	MS-7A54|1.x|WORKSTATION¡BSLI
	MS-7A59|1.x|Z270_SLI_PLUS
	MS-7A70|2.x
	MS-7A72|1.x
	MS-7A71|1.x|Z270-A_PRO
	MS-7A74|1.x
	MS-B153|1.x
	MS-7A36|1.x
	MS-7A36|2.x
	MS-7A67|2.x
	MS-7A33|2.x
	MS-7A34|2.x
	MS-7A38|2.x

VGA:
	GTX980Ti LIGHTNING
	GTX980Ti LIGHTNING(LN2)
	GTX980Ti LIGHTNING LE
	GTX1080 8GD5 DUKE
	GTX1080Ti DUKE
	GTX1070 8GD5 DUKE
	GTX1060 6G DUKE
	GTX1060 3G DUKE
