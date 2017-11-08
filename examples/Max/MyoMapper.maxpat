{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 4,
			"architecture" : "x86",
			"modernui" : 1
		}
,
		"rect" : [ 151.0, -945.0, 813.0, 640.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 632.0, 289.0, 103.0, 22.0 ],
					"style" : "",
					"text" : "route /myo1/pose"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-27",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 632.0, 325.0, 116.0, 22.0 ],
					"style" : "",
					"text" : "rest"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-26",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 215.0, 381.0, 112.0, 20.0 ],
					"style" : "",
					"text" : "EMG Scaled data."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-25",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 173.5, 224.0, 264.0, 20.0 ],
					"style" : "",
					"text" : "<- Double click to visualise all incoming data"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 414.0, 375.0, 171.0, 22.0 ],
					"style" : "",
					"text" : "route /myo1/orientation/scaled"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-42",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 590.5, 375.0, 120.0, 20.0 ],
					"style" : "",
					"text" : "Yaw, Pitch, Roll Raw"
				}

			}
, 			{
				"box" : 				{
					"candicane2" : [ 0.439216, 0.74902, 0.254902, 1.0 ],
					"candicane3" : [ 0.317647, 0.654902, 0.976471, 1.0 ],
					"candycane" : 3,
					"id" : "obj-40",
					"maxclass" : "multislider",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 604.0, 408.0, 188.0, 163.0 ],
					"setminmax" : [ 0.0, 1.0 ],
					"setstyle" : 2,
					"size" : 3,
					"slidercolor" : [ 0.784314, 0.145098, 0.023529, 1.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"candicane2" : [ 0.439216, 0.74902, 0.254902, 1.0 ],
					"candicane3" : [ 0.317647, 0.654902, 0.976471, 1.0 ],
					"candicane4" : [ 0.011765, 0.396078, 0.752941, 1.0 ],
					"candycane" : 3,
					"drawpeaks" : 1,
					"id" : "obj-38",
					"maxclass" : "multislider",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 414.0, 408.0, 188.0, 163.0 ],
					"setminmax" : [ 0.0, 1.0 ],
					"size" : 3,
					"slidercolor" : [ 0.784314, 0.145098, 0.023529, 1.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 24.0, 381.0, 194.0, 22.0 ],
					"style" : "",
					"text" : "route /myo1/emg/scaled/abs/mavg"
				}

			}
, 			{
				"box" : 				{
					"candycane" : 8,
					"drawpeaks" : 1,
					"id" : "obj-20",
					"maxclass" : "multislider",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 215.0, 408.0, 188.0, 163.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "multislider[2]",
							"parameter_shortname" : "multislider",
							"parameter_type" : 3,
							"parameter_invisible" : 1
						}

					}
,
					"setminmax" : [ 0.0, 1.0 ],
					"setstyle" : 3,
					"size" : 8,
					"style" : "",
					"varname" : "multislider[2]"
				}

			}
, 			{
				"box" : 				{
					"candycane" : 8,
					"drawpeaks" : 1,
					"id" : "obj-23",
					"maxclass" : "multislider",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 24.0, 408.0, 188.0, 163.0 ],
					"setminmax" : [ 0.0, 1.0 ],
					"size" : 8,
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 47.5, 224.0, 125.0, 22.0 ],
					"style" : "",
					"text" : "print OSC_messages"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"id" : "obj-22",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 228.5, 609.0, 53.5, 20.0 ],
					"style" : "",
					"text" : "contact"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"id" : "obj-21",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 267.5, 596.0, 36.0, 20.0 ],
					"style" : "",
					"text" : "info"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 14.0,
					"id" : "obj-18",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 24.0, 16.0, 173.0, 22.0 ],
					"style" : "",
					"text" : "Myo Mapper"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 24.0, 40.0, 494.0, 20.0 ],
					"style" : "",
					"text" : "A small example of how import Myo data into Max using Myo Mapper 3."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 215.0, 596.0, 377.0, 33.0 ],
					"style" : "",
					"text" : "For more         visit http://www.balandinodidonato.com/myomapper/ \nor               the developer: info@balandinodidonato.com"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 46.0, 313.0, 176.0, 60.0 ],
					"style" : "",
					"text" : "Change the myo's number if using multiple myos. \nEg. /myo2 to extract data from the secon Myo armband"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 24.0, 68.5, 92.0, 22.0 ],
					"style" : "",
					"text" : "loadmess 5432"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 24.0, 135.5, 79.0, 22.0 ],
					"style" : "",
					"text" : "prepend port"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "number",
					"maximum" : 99999,
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 24.0, 105.0, 90.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 124.0, 105.0, 183.0, 20.0 ],
					"style" : "",
					"text" : "Receiver OSC Port"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-82",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 24.0, 170.0, 69.0, 22.0 ],
					"style" : "",
					"text" : "udpreceive"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-82", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"order" : 1,
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-40", 0 ],
					"midpoints" : [ 423.5, 402.0, 613.5, 402.0 ],
					"order" : 0,
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 1 ],
					"midpoints" : [ 641.5, 317.5, 738.5, 317.5 ],
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"midpoints" : [ 33.5, 405.0, 224.5, 405.0 ],
					"order" : 0,
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"order" : 1,
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"midpoints" : [ 33.5, 291.0, 423.5, 291.0 ],
					"order" : 1,
					"source" : [ "obj-82", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"midpoints" : [ 33.5, 267.0, 641.5, 267.0 ],
					"order" : 0,
					"source" : [ "obj-82", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"order" : 3,
					"source" : [ "obj-82", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 0 ],
					"midpoints" : [ 33.5, 195.5, 57.0, 195.5 ],
					"order" : 2,
					"source" : [ "obj-82", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-20" : [ "multislider[2]", "multislider", 0 ]
		}
,
		"dependency_cache" : [  ],
		"autosave" : 0
	}

}
