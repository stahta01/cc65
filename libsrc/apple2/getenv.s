;
; Ullrich von Bassewitz, 2003-05-02
;
; char* __fastcall__ getenv (const char* name);
;

        .export		_getenv
        .import		return0

_getenv = return0		; "not found"

                                   
