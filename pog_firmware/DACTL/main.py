# main.py
print("Starting, LEFT SIDE")

import board

from kmk.kmk_keyboard import KMKKeyboard
from kmk.keys import KC
from kmk.scanners import DiodeOrientation
from kmk.modules.split import Split, SplitType, SplitSide
from kmk.modules.layers import Layers
# from kb import data_pin
# from kmk.extensions.RGB import RGB, AnimationModes

keyboard = KMKKeyboard()

keyboard.modules.append(Layers())

# Using drive names (REDOXL, REDOXR) to recognize sides; use split_side arg if you're not doing it
# split = Split(split_type=SplitType.UART, split_side=SplitSide.LEFT, data_pin=board.GP16, data_pin2=board.GP17, use_pio=True, uart_flip = True)
split = Split(split_type=SplitType.UART, split_side=SplitSide.LEFT, data_pin=board.GP16, data_pin2=board.GP17, use_pio=True, uart_flip = True)
keyboard.modules.append(split)

keyboard.row_pins = (board.GP2, board.GP3, board.GP4, board.GP5, board.GP6, board.GP7)
keyboard.col_pins = (board.GP8, board.GP9, board.GP10, board.GP12, board.GP13, board.GP14)
keyboard.diode_orientation = DiodeOrientation.ROW2COL

# Cleaner key names
_______ = KC.TRNS
XXXXXXX = KC.NO

# FnKey = KC.MO(1)

keyboard.keymap = [
    # Base Layer
    [
        # COL GP28		COL GP27	COL GP26	COL GP22	COL GP21	COL GP20	COL GP19	<>	COL GP18		COL GP17	COL GP16	COL GP14	COL GP13	COL GP12	COL GP11

        KC.N4,		    KC.N1,		KC.N2,		KC.N3,		KC.N4,		KC.N5,		KC.EQUAL, 		KC.N9,  		KC.N6,		KC.N7,		KC.N8,		KC.N9,		KC.RSFT,	KC.N0,\

        KC.MEH,			KC.Q,		KC.W,		KC.E,		KC.R,		KC.T,		KC.LBRACKET, 	KC.RBRACKET,	KC.Y,		KC.U,		KC.N2,		KC.O,		KC.P,		KC.MINUS,\

        KC.TAB,			KC.A,		KC.S,		KC.D,		KC.F,		KC.G,		XXXXXXX, 		KC.N4,		    KC.N3,		KC.J,		KC.K,		KC.L,		KC.SCOLON,	KC.QUOTE,\

        KC.LSHIFT,		KC.Z,		KC.X,		KC.C,		KC.V,		KC.B,		KC.LALT, 		KC.N0,    		KC.N,		KC.M,		KC.COMMA,	KC.DOT,		KC.SLASH,	KC.RSHIFT,\

        KC.LGUI,		KC.GRV,		KC.BSLASH,	KC.N3,    	KC.LCTRL,	KC.SPACE,	KC.MO(1),	 	KC.ENTER,		KC.BSPACE,	KC.N7,     	KC.LEFT,	KC.RIGHT,	KC.UP,		KC.DOWN,\

        KC.LGUI,        KC.GRV,     KC.BSLASH,  KC.N2,    KC.LCTRL,   KC.SPACE,   KC.MO(1),       KC.ENTER,       KC.BSPACE,  KC.N7,      KC.LEFT,    KC.RIGHT,   KC.UP,      KC.DOWN,\
     ]
]



if __name__ == '__main__':
    keyboard.go()
