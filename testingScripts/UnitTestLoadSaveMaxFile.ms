----------------------------------------------------------------------
--
-- Test save/load of Fabric classes in the MaxScene
--	We simply run each MaxClass unit test, save, load 
--   and validate the result
--
----------------------------------------------------------------------
rootFolder = systemTools.getEnvVariable("FABRIC3DSMAXDIR")
fileIn (rootFolder + "samples\\UnitTestMaxClassControllers.ms")
fileIn (rootFolder + "samples\\UnitTestMaxClassObject.ms")
fileIn (rootFolder + "samples\\UnitTestMaxClassModifier.ms")
fileIn (rootFolder + "samples\\UnitTestMaxClassWSModifier.ms")

fn TestLoadSaveMaxFile = 
(
	tempFile = systemTools.getEnvVariable("TEMP") + "\\temp.max"
	--------------------------------------------------------------------------------
	-- First test, controllers


	TestMaxClassControllers()
	sliderTime = 50f
	RedrawViews()
	p2_pre = $Point002.transform
	p3_pre = $Point003.transform
	
	res = saveMaxFile tempFile useNewFile:false quiet:true
	FAssert res "Failed saving file UnitTestMaxClassControllers"
	res = loadMaxFile tempFile quiet:true
	FAssert res "Failed loading file UnitTestMaxClassControllers"

	-- Validate load was successfuly
	sliderTime = 50f
	RedrawViews()
	p2_post = $Point002.transform
	p3_post = $Point003.transform
	FAssert (matricesAreEquivalent p3_pre p3_post) "Bad rotation values"
	FAssert (matricesAreEquivalent p2_pre p2_post) "Bad rotation after setting dfg float input"
	print(" -- Saved/Loaded Controllers successfully --")
	--------------------------------------------------------------------------------
	-- Next, test object
	resetMaxFile #noPrompt
	TestMaxClassObject()

	res = saveMaxFile tempFile useNewFile:false quiet:true
	FAssert res "Failed saving file UnitTestMaxClassObject"
	res = loadMaxFile tempFile quiet:true
	FAssert res "Failed loading file UnitTestMaxClassObject"

	FAssert (CompArray (GetTriMeshFaceCount $FabricMesh001) #(1530, 785)) "Bad Tri Count on Set Mesh"
	FAssert (CompBB $FabricMesh001 228.915) "Bad 5 size"
		
	print(" -- Saved/Loaded Objects successfully --")

	--------------------------------------------------------------------------------
	-- Test Modifiers
	resetMaxFile #noPrompt
	TestMaxClassModifier()
		
	$Plane001.modifiers[1].enabled = false
		
	res = saveMaxFile tempFile useNewFile:false quiet:true
	FAssert res "Failed saving file UnitTestMaxClassModifier"
	res = loadMaxFile tempFile quiet:true
	FAssert res "Failed loading file UnitTestMaxClassModifier"

	FAssert (not $Plane001.modifiers[1].enabled) "Did not save/load enabled state"
	$Plane001.modifiers[1].enabled = true
	FAssert (CompBB $Plane001 207.122) "Bad modified object size"

	print(" -- Saved/Loaded Modifiers successfully --")
		
	--------------------------------------------------------------------------------
	-- Test WSModifiers
	resetMaxFile #noPrompt
	TestMaxClassWSModifier()

	$Sphere001.modifiers[1].enabled = false
	
	res = saveMaxFile tempFile useNewFile:false quiet:true
	FAssert res "Failed saving file UnitTestMaxClassObject"
	res = loadMaxFile tempFile quiet:true
	FAssert res "Failed loading file UnitTestMaxClassObject"

	FAssert (not $Sphere001.modifiers[1].enabled) "Did not save/load enabled state"
	$Sphere001.modifiers[1].enabled = true
	FAssert (CompBB $Sphere001 131.938) "Bad WSModifier loaded size"
	print(" -- Saved/Loaded WSModifiers successfully --")
)