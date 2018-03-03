 testing 4 ways to index the array

 direct access
i=0 name=T.Seal emplNum=2901 salary=2400
i=1 name=W.Water emplNum=1100 salary=2400
i=2 name=E.Light emplNum=3387 salary=2045
i=3 name=J.Shade emplNum=1987 salary=1900
i=4 name=L.Dotty emplNum=7543 salary=3230
i=5 name=F.Gold emplNum=7990 salary=3905
i=6 name=P.Grey emplNum=1289 salary=4140
i=7 name=S.White emplNum=3523 salary=2400
i=8 name=I.Black emplNum=7003 salary=2795
i=9 name=A.Green emplNum=1876 salary=3500
i=10 name=J.Brown emplNum=4367 salary=2105

 protected access
i=0 name=T.Seal emplNum=2901 salary=2400
i=1 name=W.Water emplNum=1100 salary=2400
i=2 name=E.Light emplNum=3387 salary=2045
i=3 name=J.Shade emplNum=1987 salary=1900
i=4 name=L.Dotty emplNum=7543 salary=3230
i=5 name=F.Gold emplNum=7990 salary=3905
i=6 name=P.Grey emplNum=1289 salary=4140
i=7 name=S.White emplNum=3523 salary=2400
i=8 name=I.Black emplNum=7003 salary=2795
i=9 name=A.Green emplNum=1876 salary=3500
i=10 name=J.Brown emplNum=4367 salary=2105

 the same thing, only different indexing

 direct access
i=0 name=T.Seal emplNum=2901 salary=2400
i=1 name=W.Water emplNum=1100 salary=2400
i=2 name=E.Light emplNum=3387 salary=2045
i=3 name=J.Shade emplNum=1987 salary=1900
i=4 name=L.Dotty emplNum=7543 salary=3230
i=5 name=F.Gold emplNum=7990 salary=3905
i=6 name=P.Grey emplNum=1289 salary=4140
i=7 name=S.White emplNum=3523 salary=2400
i=8 name=I.Black emplNum=7003 salary=2795
i=9 name=A.Green emplNum=1876 salary=3500
i=10 name=J.Brown emplNum=4367 salary=2105

 protected access
i=0 name=T.Seal emplNum=2901 salary=2400
i=1 name=W.Water emplNum=1100 salary=2400
i=2 name=E.Light emplNum=3387 salary=2045
i=3 name=J.Shade emplNum=1987 salary=1900
i=4 name=L.Dotty emplNum=7543 salary=3230
i=5 name=F.Gold emplNum=7990 salary=3905
i=6 name=P.Grey emplNum=1289 salary=4140
i=7 name=S.White emplNum=3523 salary=2400
i=8 name=I.Black emplNum=7003 salary=2795
i=9 name=A.Green emplNum=1876 salary=3500
i=10 name=J.Brown emplNum=4367 salary=2105

 using the array as a stack
push: T.Seal emplNum=2901 salary=2400
push: W.Water emplNum=1100 salary=2400
push: E.Light emplNum=3387 salary=2045
push: J.Shade emplNum=1987 salary=1900
push: L.Dotty emplNum=7543 salary=3230
push: F.Gold emplNum=7990 salary=3905
push: P.Grey emplNum=1289 salary=4140
push: S.White emplNum=3523 salary=2400
push: I.Black emplNum=7003 salary=2795
push: A.Green emplNum=1876 salary=3500
push: J.Brown emplNum=4367 salary=2105
pop: J.Brown emplNum=4367 salary=2105
pop: A.Green emplNum=1876 salary=3500
pop: I.Black emplNum=7003 salary=2795
pop: S.White emplNum=3523 salary=2400
pop: P.Grey emplNum=1289 salary=4140
pop: F.Gold emplNum=7990 salary=3905
pop: L.Dotty emplNum=7543 salary=3230
pop: J.Shade emplNum=1987 salary=1900
pop: E.Light emplNum=3387 salary=2045
pop: W.Water emplNum=1100 salary=2400
pop: T.Seal emplNum=2901 salary=2400

 using the array as a heap, load twice
in heap: T.Seal emplNum=2901 salary=2400
in heap: W.Water emplNum=1100 salary=2400
in heap: E.Light emplNum=3387 salary=2045
in heap: J.Shade emplNum=1987 salary=1900
in heap: L.Dotty emplNum=7543 salary=3230
in heap: F.Gold emplNum=7990 salary=3905
in heap: P.Grey emplNum=1289 salary=4140
in heap: S.White emplNum=3523 salary=2400
in heap: I.Black emplNum=7003 salary=2795
in heap: A.Green emplNum=1876 salary=3500
in heap: J.Brown emplNum=4367 salary=2105
out heap: F.Gold emplNum=7990 salary=1400
out heap: J.Shade emplNum=1987 salary=1900
out heap: E.Light emplNum=3387 salary=2045
out heap: W.Water emplNum=1100 salary=2400
out heap: S.White emplNum=3523 salary=2400
out heap: T.Seal emplNum=2901 salary=2400
out heap: I.Black emplNum=7003 salary=2795
out heap: A.Green emplNum=1876 salary=3500
out heap: P.Grey emplNum=1289 salary=4140
out heap: L.Dotty emplNum=7543 salary=4200

 heap with a call-back function
in heap: T.Seal emplNum=2901 salary=2400
in heap: W.Water emplNum=1100 salary=2400
in heap: E.Light emplNum=3387 salary=2045
in heap: J.Shade emplNum=1987 salary=1900
in heap: L.Dotty emplNum=7543 salary=4200
in heap: F.Gold emplNum=7990 salary=1400
in heap: P.Grey emplNum=1289 salary=4140
in heap: S.White emplNum=3523 salary=2400
in heap: I.Black emplNum=7003 salary=2795
in heap: A.Green emplNum=1876 salary=3500
in heap: J.Brown emplNum=4367 salary=2105
deleted: T.Seal emplNum=2901 salary=2400
update: W.Water emplNum=1100 salary=3400
deleted: E.Light emplNum=3387 salary=2045
update: J.Shade emplNum=1987 salary=900
deleted: L.Dotty emplNum=7543 salary=4200
update: F.Gold emplNum=7990 salary=2400
deleted: P.Grey emplNum=1289 salary=4140
update: S.White emplNum=3523 salary=1400
deleted: I.Black emplNum=7003 salary=2795
update: A.Green emplNum=1876 salary=4500
deleted: J.Brown emplNum=4367 salary=2105
out heap: J.Shade emplNum=1987 salary=900
out heap: S.White emplNum=3523 salary=1400
out heap: F.Gold emplNum=7990 salary=2400
out heap: W.Water emplNum=1100 salary=3400
out heap: A.Green emplNum=1876 salary=4500
