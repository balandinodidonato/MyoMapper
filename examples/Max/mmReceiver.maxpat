{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 3,
			"architecture" : "x86",
			"modernui" : 1
		}
,
		"rect" : [ 151.0, -945.0, 523.0, 520.0 ],
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
					"fontface" : 1,
					"id" : "obj-22",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 93.5, 487.0, 53.5, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 93.5, 487.0, 53.5, 20.0 ],
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
					"patching_rect" : [ 132.5, 474.0, 36.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 132.5, 474.0, 36.0, 20.0 ],
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
					"patching_rect" : [ 39.0, 16.0, 173.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 39.0, 16.0, 173.0, 22.0 ],
					"style" : "",
					"text" : "mmReceiver"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 39.0, 40.0, 459.0, 33.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 39.0, 40.0, 459.0, 33.0 ],
					"style" : "",
					"text" : "mmReceiver extracts data from the Myo armband using Myo Mapper (http://www.balandinodidonato.com/myomapper/)."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 80.0, 474.0, 377.0, 33.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 80.0, 474.0, 377.0, 33.0 ],
					"style" : "",
					"text" : "For more         visit http://www.balandinodidonato.com/myomapper/ \nor               the developer: info@balandinodidonato.com"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 151.0, 223.0, 307.0, 33.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 151.0, 223.0, 307.0, 33.0 ],
					"style" : "",
					"text" : "Change the myo's number if using multiple myos. \nEg. /myo2 to extract data from the secon Myo armband"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 194.0, 392.0, 268.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 194.0, 392.0, 268.0, 20.0 ],
					"style" : "",
					"text" : "Open the sub-patches to visualise Myo's data"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 39.0, 98.5, 92.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 39.0, 98.5, 92.0, 22.0 ],
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
					"patching_rect" : [ 39.0, 165.5, 79.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 39.0, 165.5, 79.0, 22.0 ],
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
					"patching_rect" : [ 39.0, 135.0, 90.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 39.0, 135.0, 90.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 139.0, 135.0, 183.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 139.0, 135.0, 183.0, 20.0 ],
					"style" : "",
					"text" : "Receiver OSC Port"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 119.0, -945.0, 372.0, 198.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 59.0, 108.5, 95.0, 20.0 ],
									"style" : "",
									"text" : "Pose | int | -1, 5"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 165.0, 129.0, 116.0, 22.0 ],
									"style" : "",
									"text" : "rest"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 39.0, 134.0, 50.0, 22.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-1",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 39.0, 13.0, 30.0, 30.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-39",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "int", "" ],
									"patching_rect" : [ 39.0, 59.0, 69.0, 22.0 ],
									"style" : "",
									"text" : "unpack i s"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 98.5, 92.0, 271.5, 92.0 ],
									"source" : [ "obj-39", 1 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 263.0, 324.0, 47.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 263.0, 324.0, 47.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p pose"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 119.0, -945.0, 923.0, 601.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 674.0, 379.0, 168.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 441.0, 210.0, 168.0, 20.0 ],
									"style" : "",
									"text" : "Gyro Raw WFL | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-9",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 654.0, 401.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 631.0, 232.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-10",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 464.0, 401.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 441.0, 232.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 249.0, 379.0, 178.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 210.0, 178.0, 20.0 ],
									"style" : "",
									"text" : "Gyro Raw WFL | float | 0, 2000"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-7",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 229.0, 401.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 206.0, 232.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 2000.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-8",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 39.0, 401.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 232.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 2000.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 674.0, 143.0, 143.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 441.0, 11.0, 143.0, 20.0 ],
									"style" : "",
									"text" : "Gyro x, y, z  | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-4",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 654.0, 165.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 631.0, 33.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-5",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 464.0, 165.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 441.0, 33.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-42",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 249.0, 143.0, 178.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 11.0, 178.0, 20.0 ],
									"style" : "",
									"text" : "Guro x, y, z | float | -2000, 2000"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-40",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 229.0, 165.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 206.0, 33.0, 188.0, 163.0 ],
									"setminmax" : [ -2000.0, 2000.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"compatibility" : 1,
									"drawpeaks" : 1,
									"id" : "obj-38",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 39.0, 165.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 33.0, 188.0, 163.0 ],
									"setminmax" : [ -2000.0, 2000.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-1",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 39.0, 13.0, 30.0, 30.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-39",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 5,
									"outlettype" : [ "", "", "", "", "" ],
									"patching_rect" : [ 39.0, 59.0, 245.0, 22.0 ],
									"style" : "",
									"text" : "OSC-route /raw /scaled /rawWfL /scaledWfL"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-39", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-39", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-39", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 207.0, 324.0, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 207.0, 324.0, 44.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p gyro"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 163.0, -932.0, 919.0, 625.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 674.0, 379.0, 196.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 440.0, 214.0, 196.0, 20.0 ],
									"style" : "",
									"text" : "Acceleration Raw WFL | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-9",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 654.0, 401.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 630.0, 236.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-10",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 464.0, 401.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 440.0, 236.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 249.0, 379.0, 202.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.0, 214.0, 202.0, 20.0 ],
									"style" : "",
									"text" : "Acceleration Raw WFL | float | 0, 16"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-7",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 229.0, 401.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 205.0, 236.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 16.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-8",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 39.0, 401.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.0, 236.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 16.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 674.0, 143.0, 186.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 440.0, 14.0, 186.0, 20.0 ],
									"style" : "",
									"text" : "Acceleration x, y, z | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-4",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 654.0, 165.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 630.0, 36.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-5",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 464.0, 165.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 440.0, 36.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-42",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 249.0, 143.0, 206.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.0, 14.0, 206.0, 20.0 ],
									"style" : "",
									"text" : "Acceleration x, y, z  | float | -16, 16"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-40",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 229.0, 165.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 205.0, 36.0, 188.0, 163.0 ],
									"setminmax" : [ -16.0, 16.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"compatibility" : 1,
									"drawpeaks" : 1,
									"id" : "obj-38",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 39.0, 165.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.0, 36.0, 188.0, 163.0 ],
									"setminmax" : [ -16.0, 16.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-1",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 39.0, 54.0, 30.0, 30.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-39",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 5,
									"outlettype" : [ "", "", "", "", "" ],
									"patching_rect" : [ 39.0, 100.0, 245.0, 22.0 ],
									"style" : "",
									"text" : "OSC-route /raw /scaled /rawWfL /scaledWfL"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 473.5, 574.0, 568.5, 574.0, 568.5, 390.0, 663.5, 390.0 ],
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 48.5, 338.0, 221.5, 338.0, 221.5, 154.0, 238.5, 154.0 ],
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 218.0, 261.0, 473.5, 261.0 ],
									"source" : [ "obj-39", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 105.0, 143.0, 473.5, 143.0 ],
									"source" : [ "obj-39", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 161.5, 155.0, 48.5, 155.0 ],
									"source" : [ "obj-39", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 473.5, 338.0, 568.5, 338.0, 568.5, 154.0, 663.5, 154.0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 48.5, 574.0, 143.5, 574.0, 143.5, 390.0, 238.5, 390.0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 151.0, 357.0, 88.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 151.0, 357.0, 88.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p accelleration"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 59.0, 104.0, 933.0, 570.0 ],
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
						"visible" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 542.0, 95.0, 210.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 431.0, 22.0, 210.0, 20.0 ],
									"style" : "",
									"text" : "Quaternion, x, y, z, w  | float | -1, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-9",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 685.0, 117.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 621.0, 44.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 4,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-11",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 495.0, 117.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 431.0, 44.0, 188.0, 163.0 ],
									"setstyle" : 1,
									"size" : 4,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 517.0, 301.0, 235.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 431.0, 228.0, 235.0, 20.0 ],
									"style" : "",
									"text" : "Yaw, Pitch, Roll Scaled WFL  | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-7",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 685.0, 323.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 621.0, 250.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-8",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 495.0, 323.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 431.0, 250.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 1,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 241.0, 301.0, 211.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 23.0, 228.0, 211.0, 20.0 ],
									"style" : "",
									"text" : "Yaw, Pitch, Roll Scaled  | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-4",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 226.0, 323.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 213.0, 250.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-5",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 36.0, 323.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 23.0, 250.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 5,
									"outlettype" : [ "", "", "", "", "" ],
									"patching_rect" : [ 31.0, 50.0, 261.0, 22.0 ],
									"style" : "",
									"text" : "OSC-route /raw /scaled /scaledWfL /quaternion"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-42",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 241.0, 95.0, 211.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 18.0, 22.0, 211.0, 20.0 ],
									"style" : "",
									"text" : "Yaw, Pitch, Roll Raw | float | -PI, PI"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-40",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 221.0, 117.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 208.0, 44.0, 188.0, 163.0 ],
									"setminmax" : [ -3.141593, 3.141593 ],
									"setstyle" : 3,
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-38",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 31.0, 117.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 18.0, 44.0, 188.0, 163.0 ],
									"setminmax" : [ -3.141593, 3.141593 ],
									"size" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-10",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 31.0, 3.0, 30.0, 30.0 ],
									"style" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 222.0, 81.0, 504.5, 81.0 ],
									"source" : [ "obj-3", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 95.0, 386.0, 77.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 95.0, 386.0, 77.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p orientation"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 444.0, -945.0, 681.0, 718.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"contdata" : 1,
									"id" : "obj-64",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 470.0, 323.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 455.0, 244.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-65",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 446.0, 323.0, 24.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 431.0, 244.0, 24.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 1,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-66",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 470.0, 301.0, 217.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 431.0, 222.0, 217.0, 20.0 ],
									"style" : "",
									"text" : "EMG MAV WFL Abs | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"contdata" : 1,
									"id" : "obj-63",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 470.0, 117.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 455.0, 38.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-60",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 446.0, 117.0, 24.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 431.0, 38.0, 24.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 1,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-54",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 475.0, 95.0, 170.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 431.0, 16.0, 170.0, 20.0 ],
									"style" : "",
									"text" : "EMG MAV Abs | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-47",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 221.0, 526.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 206.0, 447.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 8,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-48",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 245.0, 502.0, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 425.0, 150.0, 20.0 ],
									"style" : "",
									"text" : "EMG Abs | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-49",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 31.0, 526.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 447.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 1,
									"size" : 8,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-46",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 221.0, 323.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 206.0, 244.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 3,
									"size" : 8,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-43",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 250.0, 296.0, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 222.0, 150.0, 20.0 ],
									"style" : "",
									"text" : "EMG Scaled | float | 0, 1"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-45",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 31.0, 323.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 244.0, 188.0, 163.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"size" : 8,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-42",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 158.0, 86.0, 186.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 16.0, 186.0, 20.0 ],
									"style" : "",
									"text" : "EMG Raw | float | -127, 128"
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-40",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 221.0, 117.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 206.0, 38.0, 188.0, 163.0 ],
									"setminmax" : [ -128.0, 127.0 ],
									"setstyle" : 3,
									"size" : 8,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"drawpeaks" : 1,
									"id" : "obj-38",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 31.0, 117.0, 188.0, 163.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 16.0, 38.0, 188.0, 163.0 ],
									"setminmax" : [ -128.0, 127.0 ],
									"size" : 8,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-10",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 31.0, 3.0, 30.0, 30.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 6,
									"outlettype" : [ "", "", "", "", "", "" ],
									"patching_rect" : [ 31.0, 44.0, 277.0, 22.0 ],
									"style" : "",
									"text" : "OSC-route /raw /scaled /scaledAbs /mav /mavWfL"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-45", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-49", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-60", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-65", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-46", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-45", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-49", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-63", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-60", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-64", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-65", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 39.0, 416.0, 48.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 39.0, 416.0, 48.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p EMG"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 39.0, 234.0, 104.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 39.0, 234.0, 104.0, 22.0 ],
					"style" : "",
					"text" : "OSC-route /myo1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 6,
					"outlettype" : [ "", "", "", "", "", "" ],
					"patching_rect" : [ 39.0, 271.0, 299.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 39.0, 271.0, 299.0, 22.0 ],
					"style" : "",
					"text" : "OSC-route /EMG /orientation /acceleration /gyro /pose"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-82",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 39.0, 200.0, 69.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 39.0, 200.0, 69.0, 22.0 ],
					"style" : "",
					"text" : "udpreceive"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-82", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-82", 0 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "OSC-route.mxo",
				"type" : "iLaX"
			}
 ],
		"autosave" : 0
	}

}
