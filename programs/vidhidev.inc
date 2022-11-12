; ------------------------------------------------------------------
; Include file for VidHIOS program development 
; ------------------------------------------------------------------

; ------------------------------------------------------------------
; IMPORTANT LOCATIONS

os_main			equ	0000h	; Where the OS code starts


; ------------------------------------------------------------------
; COLOURS (eg for os_draw_background and os_draw_block)

%DEFINE BLACK_ON_WHITE		11110000b
%DEFINE WHITE_ON_BLACK		00001111b
%DEFINE WHITE_ON_LIGHT_RED	11001111b
%DEFINE WHITE_ON_GREEN		00101111b
%DEFINE RED_ON_LIGHT_GREEN	01011101b


; ------------------------------------------------------------------
; KEYS

%DEFINE KEY_UP		72
%DEFINE KEY_DOWN	80
%DEFINE KEY_LEFT	75
%DEFINE KEY_RIGHT	77

%DEFINE KEY_ESC	27
%DEFINE KEY_ENTER	13


; ------------------------------------------------------------------
; SYSTEM CALLS

; Screen control


os_print_string	equ	0003h	; SI = zero-terminated string location
os_move_cursor		equ	0006h	; DH, DL = row, column
os_draw_background	equ	002Ah	; AX, BX = strings, CX = colour
os_dialog_box		equ	003Ch	; AX, BX, CX = strings, DX = type
					; OUT: AX = 0 for OK, 1 for cancel
					; (only multi choice for DX = 1)
os_wait_for_key	equ	0012h	; Returns AL = key pressed

; Misc OS functions

os_run_basic		equ	00C6h	; AX = code location in RAM, BX = size,
					; SI = parameter string (or 0 if none)
os_get_api_version	equ	0057h	; Returns API version in AL
os_pause		equ	0024h	; AX = 10ths of second to wait
os_fatal_error		equ	0027h	; AX = error string location


; ------------------------------------------------------------------

