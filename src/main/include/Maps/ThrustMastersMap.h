#pragma once

enum ThrustJoystickAxis {
	xAxisJS, yAxisJS, rotateJS, throttleJS
};

enum ThrustJoystickButtons {
	trigger = 1,
	thumbSwitch,
	leftButton,
	rightButton,
	topLeftLeft,
	topLeftMiddle,
	topLeftRight,
	bottomLeftRight,
	bottomLeftMiddle,
	bottomLeftLeft,
	topRightRight,
	topRightMiddle,
	topRightLeft,
	bottomRightLeft,
	bottomRightMiddle,
	bottomRightRight
};

enum ThrustThrottleAxis {
	xAxisTR,
	yAxisTR,
	zAxisTR,
	deadXRotateTR,
	deadYRotateTR,
	paddleTR,
	sliderTR
};

enum ThrustThrottleButtons {
	rightThumbOrange = 1,
	topLittleFingerButton,
	topRingFingerButton,
	flipOffTop,
	flipOffBottom,
	axisButton,
	middleHatUp,
	middleHatForward,
	middleHatDown,
	middleHatBackward,
	bottomHatUp,
	bottomHatForward,
	bottomHatDown,
	bottomHatBackward

};
