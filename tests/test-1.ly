% Automatically generated from a musicxml file.
\version "2.22.1"

#(set-global-staff-size 20.0025)



#(set! paper-alist
(cons '("new_size" . (cons (* 215.9 mm) (* 279.4 mm))) paper-alist))
\paper {
    #(set-paper-size "new_size")
    top-margin = 10\mm
    bottom-margin = 20\mm
    left-margin = 10\mm
    right-margin = 10\mm
    ragged-last-bottom = ##f
}

\header {
    composer = "Niccolò Paganini"
    subtitle = "Op. 1, No. 24"
    title = "Violin Caprice No. 24 in A Minor"
}

part-Pone-one = {
    \key c \major
    \time 2/4
    \clef treble
    a'8-\markup { \bold "Quasi Presto" }\p-\markup { \bold "Tema" } r16 a'16
    a'16( c''16 b'16 a'16) |
    e''8 r16 e'16 e'16( gis'16 fis'16 e'16) |
    a'8 r16 a'16 a'16( c''16 b'16 a'16) |
    e''4(-> e'8) r8 |
    a''8 r16 a''16 a''16( bes''16 a''16 g''16) |
% 5
    f''8 r16 d''16 d''16( f''16 e''16 d''16) |
    g''8 r16 g''16 g''16( a''16 g''16 f''16) |
    e''8 r16 c''16 c''16( e''16 d''16 c''16) |
    f''8 r16 b'16 b'16( d''16 c''16 b'16) |
    e''8 r16 a'16 a'16( c''16 b'16 a'16) |
% 10
    f'8 r16 dis''16 e'16( e''16 d''16 b'16) |
    a'4(-> a8) r8 |
    \time 2/4
    \slashedGrace { a''16(\f-\markup { \bold "Var. 1" } c'''16 } \tuplet 3/2 {
    e'''8)-> c'''8(-. a''8-. } \tuplet 3/2 { e''8-. c''8-. a'8)-. } |
    \slashedGrace { e''16( gis''16 } \tuplet 3/2 { b''8)-> gis''8(-. e''8-. }
    \tuplet 3/2 { b'8-. gis'8-. e'8)-. } |
    \slashedGrace { a''16( c'''16 } \tuplet 3/2 { e'''8)-> c'''8(-. a''8-. }
    \tuplet 3/2 { e''8-. c''8-. a'8)-. } |
% 15
    e''4(-> e'8) r8 |
    \slashedGrace { cis'''16( e'''16 } \tuplet 3/2 { a'''8)-> e'''8(-.
    cis'''8-. } \tuplet 3/2 { a''8-. e''8-. cis''8)-. } |
    \slashedGrace { d'16( f'16 } \tuplet 3/2 { a'8) d''8(-. f''8-. } \tuplet
    3/2 { a''8-. d'''8-. f'''8)-. } |
    \slashedGrace { b''16( d'''16 } \tuplet 3/2 { g'''8)-> d'''8(-. b''8-. }
    \tuplet 3/2 { g''8-. d''8-. b'8)-. } |
    \slashedGrace { c'16( e'16 } \tuplet 3/2 { g'8) c''8(-. e''8-. } \tuplet
    3/2 { g''8-. c'''8-. e'''8)-. } |
% 20
    \slashedGrace { f'''16( d'''16 } \tuplet 3/2 { b''8) gis''8(-. f''8-. }
    \tuplet 3/2 { d''8-. b'8-. gis'8)-. } |
    \slashedGrace { e'''16( c'''16 } \tuplet 3/2 { a''8) e''8(-. c''8-. }
    \tuplet 3/2 { a'8-. e'8-. c'8)-. } |
    \slashedGrace { d'16( f'16 } \tuplet 3/2 { b'8 d''8 f''8) } \tuplet 3/2 {
    e'8 e''8 gis'8 } |
    a'4(-> a8) r8 |
    \time 2/4
    a'16(\p-\markup { \bold "Var. 2" } gis'16 a'16 gis'16 \slashedGrace {
    bes'16 } a'16-> b'16 c''16 d''16) |
% 25
    e''16( dis''16 e''16 dis''16 \slashedGrace { f''16 } e''16-> d''16 c''16
    b'16) |
    a'16( gis'16 a'16 gis'16 \slashedGrace { bes'16 } a'16-> b'16 c''16 d''16) |
    e''16( dis''16 e''16 dis''16) \slashedGrace { f''16 } e''8 e'8 |
    a''16( gis''16 a''16 gis''16 \slashedGrace { bes''16 } a''16 g''16 f''16
    e''16) |
    d''16( cis''16 d''16 cis''16 \slashedGrace { ees''16 } d''16 e''16 f''16
    d''16) |
% 30
    g''16(-\markup { \italic "simile" } fis''16 g''16 fis''16 \slashedGrace {
    aes''16 } g''16 f''16 e''16 d''16) |
    c''16( b'16 c''16 b'16 \slashedGrace { des''16 } c''16 d''16 e''16 c''16) |
    f''16( e''16 f''16 e''16 \slashedGrace { g''16 } f''16 d''16 c''16 b'16) |
    e''16( dis''16 e''16 dis''16 \slashedGrace { f''16 } e''16 c''16 b'16
    a'16) |
    b'16( ais'16 b'16 ais'16 \slashedGrace { c''16 } b'16 f''16 e''16 gis'16) |
% 35
    a'16( gis'16 a'16 gis'16) \slashedGrace { b'16 } a'8 r8 |
    \time 2/4
    <c' c'' >4.(-\markup { \bold "Var. 3" }-\markup { \italic "sempre sul G e
    D" }\mf <a a' >8 |
    <gis gis' >8-> <b b' >8 <e' e'' >4) |
    <c' c'' >4.( <a a' >8 |
    <b b' >8-> <dis' dis'' >8-> <f' f'' >8-> <e' e'' >8)-> |
% 40
    <a' a'' >4.( <cis' cis'' >8 |
    <d' d'' >8-> <e' e'' >8-> <f' f'' >8-> <fis' fis'' >8)-> |
    <g' g'' >4.( <b b' >8 |
    <c' c'' >8-> <d' d'' >8-> <dis' dis'' >8-> <e' e'' >8-> |
    <f' f'' >4. <b b' >8) |
% 45
    <e' e'' >4.( <a a' >8 |
    <b b' >8 <f' f'' >8 <e' e'' >8 <gis gis' >8) |
    <b b' >4( <a a' >8) r8 |
    \time 2/4
    a''16(\p-\markup { \bold "Var. 4" } a'''16 gis'''16 g'''16 fis'''16 f'''16
    e'''16 dis'''16 |
    f'''16 e'''16 dis'''16 f'''16 e'''16 b''16 gis''16 e''16) |
% 50
    a''16( a'''16 gis'''16 g'''16 fis'''16 f'''16 e'''16 dis'''16 |
    f'''16 e'''16 dis'''16 f'''16 e'''8) e''8 |
    a''16( a'''16 gis'''16 g'''16 fis'''16 f'''16 e'''16 d'''16) |
    cis'''16( e'''16 a''16 cis'''16 d'''16 a''16 f''16 d''16) |
    g''16( g'''16 fis'''16 f'''16 e'''16 ees'''16 d'''16 c'''16) |
% 55
    b''16( d'''16 g''16 b''16 c'''16 g''16 e''16 c''16) |
    f''16( f'''16 e'''16 ees'''16 d'''16 cis'''16 c'''16 b''16) |
    e''16( e'''16 dis'''16 d'''16 cis'''16 c'''16 b''16 a''16) |
    f''16( e''16 ees''16 d''16 cis''16 c''16 b'16 gis'16) |
    a'16 a'''16 e'''16 c'''16 a''16 e''16 c''16 a'16 |
% 60
    \time 2/4
    a8->-\markup { \bold "Var. 5" }\mf f''16( f'16 e''16 e'16) a8(-> |
    gis8) dis'''16( dis''16 e'''16 e''16) gis8(-> |
    a8) f''16( f'16 e''16 e'16) a8(-> |
    gis8) dis'''16( dis''16 e'''16 e''16) r8 |
    cis'8-> bes'''16( bes''16 a'''16 a''16) cis'8(-> |
% 65
    d'8) e''16( e'16 f''16 f'16) c'8(-> |
    b8) aes'''16( aes''16 g'''16 g''16) b8(-> |
    c'8) dis''16( dis'16 e''16 e'16) c'8(-> |
    d'8) b''16( b'16 bes''16 bes'16) d'8(-> |
    e'8) gis''16( gis'16 a''16 a'16) f'8(-> |
% 70
    d'8) f'''16( f''16 e'''16 e''16) e'8(-> |
    a8) c'''16( c''16 a''16 a'16) r8 |
    \time 2/4
    <c''' e''' >4.(\f-\markup { \bold "Var. 6" } <b'' d''' >16 <a'' c''' >16 |
    <gis'' b'' >16 <f'' a'' >16 <e'' gis'' >16 <d'' f'' >16 <c'' e'' >16 <b'
    d'' >16 <a' c'' >16 <gis' b' >16) |
    <a' c'' >4.( <b' d'' >16 <c'' e'' >16 |
% 75
    <b' d'' >16 <a' c'' >16 <gis' b' >16 <f' a' >16 <e' gis' >4) |
    <a' cis''' >4.( <b' d''' >16 <cis'' e''' >16 |
    <d'' f''' >16 <e'' g''' >16 <f'' a''' >16 <g'' b''' >16 <a'' cis'''' >16
    <b'' d'''' >16 <cis''' e'''' >16 <d''' f'''' >16) |
    <g b' >4.( <a c'' >16 <b d'' >16 |
    <c' e'' >16 <d' f'' >16 <e' g'' >16 <f' a'' >16 <g' b'' >16 <a' c''' >16
    <b' d''' >16 <c'' e''' >16) |
% 80
    <d'' f''' >4.( <c'' e''' >16 <b' d''' >16) |
    <c'' e''' >4.( <b' d''' >16 <a' c''' >16) |
    <d' f'' >8( <e' e'' >16 <f' d'' >16 <e' c'' >16 <a' c'' >16 <e' b' >16
    <gis' b' >16) |
    << { a'4 a8) r8 } \\ { a'4( r8 r8 } >> |
    \time 2/4
    \tuplet 3/2 { e'''16(\p-\markup { \bold "Var. 7" } f'''16 e'''16) }
    c'''4-> \tuplet 3/2 { a''16( b''16 a''16) } |
% 85
    \tuplet 3/2 { b''16( c'''16 b''16) } \tuplet 3/2 { gis''16( a''16 gis''16)
    } \tuplet 3/2 { e''16( f''16 e''16) } e'8 |
    \tuplet 3/2 { e'''16( f'''16 e'''16) } c'''4-> \tuplet 3/2 { a16( b16 a16)
    } |
    \tuplet 3/2 { b16( c'16 b16) } \tuplet 3/2 { e'16( f'16 e'16) } \tuplet
    3/2 { gis'16( a'16 gis'16) } e'8 |
    \tuplet 3/2 { e'''16( f'''16 e'''16) } cis'''4-> \tuplet 3/2 { a''16(
    bes''16 a''16) } |
    \tuplet 3/2 { d'''16( e'''16 d'''16) } \tuplet 3/2 { a'16( bes'16 a'16) }
    \tuplet 3/2 { f'16( g'16 f'16) } \tuplet 3/2 { d'16( e'16 d'16) } |
% 90
    \tuplet 3/2 { d'''16( e'''16 d'''16) } b''4-> \tuplet 3/2 { g''16( a''16
    g''16) } |
    \tuplet 3/2 { c'''16( d'''16 c'''16) } \tuplet 3/2 { g'16( a'16 g'16) }
    \tuplet 3/2 { e'16( f'16 e'16) } \tuplet 3/2 { c'16( d'16 c'16) } |
    \tuplet 3/2 { d'''16( e'''16 d'''16) } f'''4-> \tuplet 3/2 { d'16( e'16
    d'16) } |
    \tuplet 3/2 { c'''16( d'''16 c'''16) } e'''4-> \tuplet 3/2 { c'16( d'16
    c'16) } |
    \tuplet 3/2 { d'''16( e'''16 d'''16) } \tuplet 3/2 { b16( c'16 b16) }
    \tuplet 3/2 { b''16( c'''16 b''16) } \tuplet 3/2 { gis16( a16 gis16) } |
% 95
    \tuplet 3/2 { a16( b16 a16) } \tuplet 3/2 { a''16( b''16 a''16) } a8 r8 |
    \time 2/4
    <a' c'' e'' >8\f-\markup { \bold "Var. 8" } <c'' e'' e'' >8 <b' d'' e'' >8
    <a' c'' e'' >8 |
    <gis' b' e'' >8 <e' b' b'' >8 <fis' a' b'' >8 <gis' b' e'' >8 |
    <a' c'' e'' >8 <c'' e'' e'' >8 <b' d'' e'' >8 <a' c'' e'' >8 |
    <gis' b' e'' >8 <f' dis'' a'' >8 <e' e'' gis'' >8 <e' b' e'' >8 |
% 100
    <a' cis'' e'' >8 <b' d'' e'' >8 <cis'' e'' e'' >8 <a' cis'' e'' >8 |
    <d' f'' d''' >8 <d' g'' e''' >8 <d' a'' f''' >8 <d' f'' d''' >8 |
    <g d' b' >8 <g e' c'' >8 <g f' d'' >8 <g d' b' >8 |
    <c' g' e'' >8 <d' g' f'' >8 <e' g' g'' >8 <c' g' e'' >8 |
    <d' b' f'' >8 <d' b' d'' >8 <d' b' e'' >8 <d' b' f'' >8 |
% 105
    <c' c'' e'' >8 <b b' d'' >8 <a a' c'' >8 <a g' cis'' >8 |
    <d' f' d'' >8 <dis' c'' a'' >8 <e' c'' a'' >8 <e' b' gis'' >8 |
    <a' c'' a'' >4( a8) r8 |
    \time 2/4
    c'''16-\markup { \bold "Var. 9" } a''16-\markup { "p" } e''16
    c''16-\markup { "a" } a'16-\markup { "p" } e''16-\markup { "a" }
    c''16-\markup { "p" } a'16 |
    b''16-\markup { "a" } gis''16-\markup { "p" } e''16 d'''16-\markup { "a" }
    b''16-\markup { "p" } e''16 gis''16-\markup { "a" } e''16-\markup { "p" } |
% 110
    c'''16-\markup { "a" } a''16-\markup { "p" } e''16 c''16-\markup { "a" }
    a'16-\markup { "p" } e''16-\markup { "a" } c''16-\markup { "p" } a'16 |
    b''16-\markup { "a" } gis''16-\markup { "p" } e''16 e''16-\markup { "a" }
    b'16-\markup { "p" } gis'16-\markup { "a" } e'8-\markup { "p" } |
    e'''16-\markup { "a" } cis'''16-\markup { "p" } a''16 e''16
    cis''16-\markup { "a" } a'16-\markup { "p" } g'16-\markup { "a" }
    e'16-\markup { "p" } |
    f'16-\markup { "a" } d'16-\markup { "p" } d'''16-\markup { "a" }
    a''16-\markup { "p" } f''16-\markup { "a" } d''16-\markup { "p" }
    f'16-\markup { "a" } d'16-\markup { "p" } |
    d'''16-\markup { "a" } b''16-\markup { "p" } g''16 f''16 d''16-\markup {
    "a" } b'16-\markup { "p" } f'16-\markup { "a" } d'16-\markup { "p" } |
% 115
    e'16-\markup { "a" } c'16-\markup { "p" } c'''16-\markup { "a" }
    g''16-\markup { "p" } e''16-\markup { "a" } c''16-\markup { "p" }
    g'16-\markup { "a" } c'16-\markup { "p" } |
    b''16-\markup { "a" } a''16-\markup { "p" } gis''16 f''16 e''16
    d''16-\markup { "a" } c''16-\markup { "p" } b'16 |
    a'16 g'16-\markup { "a" } f'16-\markup { "p" } e'16 d'16 c'16-\markup {
    "a" } b16-\markup { "p" } a16 |
    f'16-\markup { "a" } d'16-\markup { "p" } a''16-\markup { "a" }
    f''16-\markup { "p" } gis'16-\markup { "a" } e'16-\markup { "p" }
    b''16-\markup { "a" } gis''16-\markup { "p" } |
    a''16-\markup { "a" } e''16-\markup { "p" } c''16-\markup { "a" }
    a'16-\markup { "p" } a8 r8-\markup { "a" } |
% 120
    \time 2/4
    a'''4.(\p-\markup { \bold "Var. 10" } e'''16 c''''16 |
    b'''16 a'''16 gis'''16 fis'''16 e'''16 fis'''16 gis'''16 e'''16) |
    a'''4( a'''16 b'''16 c''''16 d''''16 |
    dis''''8. e''''16) e'''4 |
    a'''4 a'''16 e''''16 cis''''16 a'''16 |
% 125
    g'''16 e'''16 cis'''16 a''16 g''16 f''16 e''16 d''16 |
    g'''4 g'''16 d''''16 b'''16 g'''16 |
    f'''16 d'''16 b''16 g''16 f''16 e''16 d''16 c''16 |
    f'''4 f'''16 d'''16 b''16 a''16 |
    gis''16 e''16 d''16 b'16 c''16 e''16 a''16 g''16 |
% 130
    f''16 d'''16 b''16 a''16 gis''16 b'''16 gis'''16 e'''16 |
    \slashedGrace { gis'''16 } a'''4( a''8) r8 |
    \time 2/4
    <c' e' >16(\f-\markup { \bold "Var. 11" } <a' e'' >16) <c' e' >16( <a' e''
    >16) <b gis' >16( <b' e'' >16) <a e' >16( <c'' e'' >16) |
    gis32( b32 e'32 gis'32 b'32 e''32 gis''32 b''32) e'''16 gis'''16 b'''16
    e''''16 |
    <c' e' >16( <a' e'' >16) <c' e' >16( <a' e'' >16) <b gis' >16( <e'' b''
    >16) <a e' >16( <c'' a'' >16) |
% 135
    <gis e' >16 e'''16 b''16 gis''16 e''16 b'16 gis'16 e'16 |
    <cis' a' >16( <e'' cis''' >16) <cis' a' >16( <e'' cis''' >16) <d' a' >16(
    <f'' d''' >16) <e' cis'' >16( <a'' e''' >16) |
    \tuplet 7/4 { f'16( d'16 f'16 a'16 d''16 f''16 a''16) } d'''16 f'''16
    a'''16 d''''16 |
    <b g' >16( <d'' b'' >16) <b g' >16( <d'' b'' >16) <c' g' >16( <e'' c'''
    >16) <d' b' >16( <g'' d''' >16) |
    \tuplet 7/4 { e'16( c'16 e'16 g'16 c''16 e''16 g''16) } c'''16 e'''16
    g'''16 c''''16 |
% 140
    <d' b' >16( <f'' d''' >16) <d' b' >16( <f'' d''' >16) <c' a' >16( <e''
    c''' >16) <b gis' >16( <e'' b'' >16) |
    <a e' >16( <c'' a'' >16) <b gis' >16( <e'' b'' >16) <c' a' >16( <e'' c'''
    >16) <dis' c'' >16( <a'' fis''' >16) |
    \tuplet 6/4 { e'16( a'16 c''16 e''16 a''16 c'''16) } \tuplet 6/4 { e'16(
    gis'16 b'16 e''16 gis''16 b''16) } |
    \tuplet 6/4 { a16(\p-\markup { \bold "Finale" } c'16 e'16 a'16 c''16
    e''16) } \tuplet 6/4 { a''16( e''16 c''16 a'16 e'16 c'16) } |
    \tuplet 6/4 { a16( cis'16 e'16 a'16 cis''16 e''16) } \tuplet 6/4 { a''16(
    e''16 cis''16 a'16 e'16 cis'16) } |
% 145
    \tuplet 6/4 { d'16( f'16 a'16 d''16 f''16 a''16) } d'''16 f'''16 a'''16
    d''''16 |
    <gis f' >16(\f <d'' b'' >16) <b gis' >16( <f'' d''' >16) <d' b' >16(
    <gis'' f''' >16) <gis f' >16( <d'' b'' >16) |
    \tuplet 6/4 { a16(\p c'16 e'16 a'16 c''16 e''16) } \tuplet 6/4 { a''16(
    e''16 c''16 a'16 e'16 c'16) } |
    \tuplet 6/4 { a16( cis'16 e'16 a'16 cis''16 e''16) } \tuplet 6/4 { a''16(
    e''16 cis''16 a'16 e'16 cis'16) } |
    \tuplet 6/4 { d'16( f'16 a'16 d''16 f''16 a''16) } d'''16 f'''16 a'''16
    d''''16 |
% 150
    <gis f' >16(\f <d'' b'' >16) <b gis' >16( <f'' d''' >16) <d' b' >16(
    <gis'' f''' >16) <gis f' >16( <d'' b'' >16) |
    \key a \major
    \tuplet 6/4 { a16(\p\< cis'16 e'16 a'16 cis''16 e''16 } \tuplet 6/4 {
    a''16 e''16 cis''16 a'16 e'16 cis'16) } |
    \tuplet 7/4 { a16( cis'16 e'16 a'16 cis''16 e''16 a''16 } \tuplet 7/4 {
    cis'''16 a''16 e''16 cis''16 a'16 e'16 cis'16) } |
    \tuplet 8/4 { a16( cis'16 e'16 a'16 cis''16 e''16 a''16 cis'''16 } \tuplet
    8/4 { e'''16 cis'''16 a''16 e''16 cis''16 a'16 e'16 cis'16) } |
    \tuplet 9/4 { a16( cis'16 e'16 a'16 cis''16 e''16 a''16 cis'''16 e'''16 }
    \tuplet 9/4 { a'''16 e'''16 cis'''16 a''16 e''16 cis''16 a'16 e'16 cis'16)
    } |
% 155
    a2(\trill |
    a2\trill |
    <a e' cis'' a'' >8)\ff r8 r4 |
}

\score {
    \new Staff \part-Pone-one
}
