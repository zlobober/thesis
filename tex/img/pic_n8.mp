prologues := 3

input latexmp;

u = 5cm;

beginfig(1)
    pair O;
    O := (5u, 5u);
    pair p[];
    pair h;
    R := 7u;
    r := 3u;
    f := 0.06;
    e := 0.15;
    for i = 0 upto 7:
        p[i] := O + R*(cosd(i*45), sind(i*45));
    endfor;
    p[8] := p[0];
    for i = 0 upto 7:
        h := (p[i] + p[i+1] - 2O);
        draw (p[i] + f*h) -- (p[i + 1] + f*h);
        draw (p[i] - f*h) -- (p[i + 1] - f*h);
    endfor;
    for i = 1 step 2 until 7:
        draw (p[i] + (p[i+1] - p[i])*e) -- O;
        draw (p[i] - (p[i+1] - p[i])*e) -- O;
        fill fullcircle scaled r shifted p[i] withcolor white;
    endfor;
    for i = 0 step 2 until 6:
        fill fullcircle scaled r shifted p[i] withcolor 0.9 white;
    endfor;
    for i = 0 upto 7:
        draw fullcircle scaled r shifted p[i];
        draw thelabel(textext("$S_" & decimal i & "$"), (0,0)) scaled 0.1u shifted p[i];
    endfor;
    fill fullcircle scaled 0.5r shifted O withcolor white;
    draw fullcircle scaled 0.5r shifted O;
    draw thelabel(textext("$c$"), (0,0)) scaled 0.1u shifted O; 
endfig;

end.
