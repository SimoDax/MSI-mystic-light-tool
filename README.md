# MSI-mystic-light-tool

Open project to implement our own led effects for Mystic Light-enabled MSI products

You may know that MSI has released a [C# SDK](https://msi.com/Landing/mystic-light-motherboard#extension) to embed led control in third-parties applications. As the official Gaming App doesn't support much effects (and in my case, I'm limited to 7 colors), I'm planning to code a customizable led tool to get the most out of our leds :)

UPDATE (16/11): I've actually tested the library. It needs Mystic Light to be installed, as such, it only supports a few MSI products, and my gear is not in the list. I'll just post some stubs on how to use it I think, as I'll never be able to test it.
For reference, here's a link to [Mystic Light 1 installer](http://download.msi.com/uti_exe/Mystic_Light.zip), and another one to [Mystic light 2](http://download.msi.com/uti_exe/Mystic_Light_2.zip). 
This should be the supported hardware list:

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
