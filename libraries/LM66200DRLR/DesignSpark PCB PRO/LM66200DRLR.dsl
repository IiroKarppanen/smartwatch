SamacSys ECAD Model
15089388/1182104/2.50/8/2/Integrated Circuit

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r47.5_30"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.3) (shapeHeight 0.475))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "SOTFL50P160X60-8N" (originalName "SOTFL50P160X60-8N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r47.5_30) (pt -0.838, 0.75) (rotation 90))
			(pad (padNum 2) (padStyleRef r47.5_30) (pt -0.838, 0.25) (rotation 90))
			(pad (padNum 3) (padStyleRef r47.5_30) (pt -0.838, -0.25) (rotation 90))
			(pad (padNum 4) (padStyleRef r47.5_30) (pt -0.838, -0.75) (rotation 90))
			(pad (padNum 5) (padStyleRef r47.5_30) (pt 0.838, -0.75) (rotation 90))
			(pad (padNum 6) (padStyleRef r47.5_30) (pt 0.838, -0.25) (rotation 90))
			(pad (padNum 7) (padStyleRef r47.5_30) (pt 0.838, 0.25) (rotation 90))
			(pad (padNum 8) (padStyleRef r47.5_30) (pt 0.838, 0.75) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.225 1.25) (pt 1.225 1.25) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.225 1.25) (pt 1.225 -1.25) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.225 -1.25) (pt -1.225 -1.25) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.225 -1.25) (pt -1.225 1.25) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.6 1.05) (pt 0.6 1.05) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.6 1.05) (pt 0.6 -1.05) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.6 -1.05) (pt -0.6 -1.05) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.6 -1.05) (pt -0.6 1.05) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.6 0.55) (pt -0.1 1.05) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.25 1.05) (pt 0.25 1.05) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0.25 1.05) (pt 0.25 -1.05) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0.25 -1.05) (pt -0.25 -1.05) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.25 -1.05) (pt -0.25 1.05) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.075 1.15) (pt -0.6 1.15) (width 0.2))
		)
	)
	(symbolDef "LM66200DRLR" (originalName "LM66200DRLR")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 3) (pt 0 mils -200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -225 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 4) (pt 0 mils -300 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -325 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 5) (pt 1300 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1070 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(pin (pinNum 6) (pt 1300 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1070 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(pin (pinNum 7) (pt 1300 mils -200 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1070 mils -225 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(pin (pinNum 8) (pt 1300 mils -300 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1070 mils -325 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 1100 mils 100 mils) (width 6 mils))
		(line (pt 1100 mils 100 mils) (pt 1100 mils -400 mils) (width 6 mils))
		(line (pt 1100 mils -400 mils) (pt 200 mils -400 mils) (width 6 mils))
		(line (pt 200 mils -400 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 1150 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "LM66200DRLR" (originalName "LM66200DRLR") (compHeader (numPins 8) (numParts 1) (refDesPrefix IC)
		)
		(compPin "1" (pinName "GND_1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "VOUT_1") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "VIN1") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "4" (pinName "__ON") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "5" (pinName "GND_2") (partNum 1) (symPinNum 5) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "6" (pinName "VIN2") (partNum 1) (symPinNum 6) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "7" (pinName "VOUT_2") (partNum 1) (symPinNum 7) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "8" (pinName "ST") (partNum 1) (symPinNum 8) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "LM66200DRLR"))
		(attachedPattern (patternNum 1) (patternName "SOTFL50P160X60-8N")
			(numPads 8)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
				(padNum 5) (compPinRef "5")
				(padNum 6) (compPinRef "6")
				(padNum 7) (compPinRef "7")
				(padNum 8) (compPinRef "8")
			)
		)
		(attr "Mouser Part Number" "595-LM66200DRLR")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Texas-Instruments/LM66200DRLR?qs=Rp5uXu7WBW90hnpZAkIOdQ%3D%3D")
		(attr "Manufacturer_Name" "Texas Instruments")
		(attr "Manufacturer_Part_Number" "LM66200DRLR")
		(attr "Description" "1.6-V to 5.5-V, 40-m, 2.5-A, low-IQ, dual ideal diode")
		(attr "Datasheet Link" "https://www.ti.com/lit/gpn/lm66200")
		(attr "Height" "0.6 mm")
	)

)
