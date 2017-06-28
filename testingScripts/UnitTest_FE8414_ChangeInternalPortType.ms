fn TestFE8414 =
(
	sm = FabricMesh()
	func = sm.DFGAddFunc "func" "dfgEntry {
	  // result = a + b;
	}
	" [656.000000,90.000000]  execPath:""
	port = sm.DFGAddPort "v" #DFGPortIN "Scalar" execPath:func
	
	res = sm.DFGEditPort port #DFGPortIO execPath:func
	FAssert(res == port) "Could not reset port type"
	print "test for FE-8414 passed"
)