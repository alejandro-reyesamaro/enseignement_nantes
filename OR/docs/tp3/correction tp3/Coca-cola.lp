\* Problem: Coca-cola *\

Maximize
 obj: + 53 xA + 46 xB + 16 xC + 28 xD + 96 xE + 84 xF + 32 xG + 21 xH
 + 15 xI + 22 xJ + 41 xK + 53 xL + 66 xM

Subject To
 VilleA: - yD - yC - yB - yA + xA <= 0
 VilleB: - yG - yF - yE - yD - yC - yB - yA + xB <= 0
 VilleC: - yD - yC - yB - yA + xC <= 0
 VilleD: - yK - yJ - yG - yF - yE - yD - yC - yB - yA + xD <= 0
 VilleE: - yK - yJ - yI - yG - yF - yE - yD - yB + xE <= 0
 VilleF: - yK - yJ - yI - yG - yF - yE - yD - yB + xF <= 0
 VilleG: - yK - yJ - yI - yH - yG - yF - yE - yD - yB + xG <= 0
 VilleH: - yM - yL - yK - yJ - yI - yH - yG + xH <= 0
 VilleI: - yL - yK - yJ - yI - yH - yG - yF - yE + xI <= 0
 VilleJ: - yL - yK - yJ - yI - yH - yG - yF - yE - yD + xJ <= 0
 VilleK: - yL - yK - yJ - yI - yH - yG - yF - yE - yD + xK <= 0
 VilleL: - yM - yL - yK - yJ - yI - yH + xL <= 0
 VilleM: - yM - yL - yH + xM <= 0
 Last: + yM + yL + yK + yJ + yI + yH + yG + yF + yE + yD + yC + yB + yA
 = 2

Bounds
 0 <= xA <= 1
 0 <= xB <= 1
 0 <= xC <= 1
 0 <= xD <= 1
 0 <= xE <= 1
 0 <= xF <= 1
 0 <= xG <= 1
 0 <= xH <= 1
 0 <= xI <= 1
 0 <= xJ <= 1
 0 <= xK <= 1
 0 <= xL <= 1
 0 <= xM <= 1
 0 <= yA <= 1
 0 <= yB <= 1
 0 <= yC <= 1
 0 <= yD <= 1
 0 <= yE <= 1
 0 <= yF <= 1
 0 <= yG <= 1
 0 <= yH <= 1
 0 <= yI <= 1
 0 <= yJ <= 1
 0 <= yK <= 1
 0 <= yL <= 1
 0 <= yM <= 1

Generals
 xA
 xB
 xC
 xD
 xE
 xF
 xG
 xH
 xI
 xJ
 xK
 xL
 xM
 yA
 yB
 yC
 yD
 yE
 yF
 yG
 yH
 yI
 yJ
 yK
 yL
 yM

End
