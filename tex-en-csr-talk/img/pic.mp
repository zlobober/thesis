input metagraph;
input latexmp;

prologues := 3

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

beginfig(2)
    pair p[];
    R := 7u;
    r := 2.5u;
    pair O;
    O := (5u, 5u);
    p[0] := O + R * (cosd(-45), sind(-45));
    p[1] := O + (-R/3, 0);
    p[2] := O + (R/3, 0);
    p[3] := O + R * (cosd(-135), sind(-135));
    p[4] := O + R * (cosd(180), sind(180));
    p[5] := O + R * (cosd(-90), sind(-90));
    p[6] := O + R * (cosd(45), sind(45));
    p[7] := O + R * (cosd(0), sind(0));
    p[8] := O + R * (cosd(135), sind(135));
    p[9] := O + R * (cosd(90), sind(90));
    draw p[7] -- p[0];
    draw p[0] -- p[5];
    draw p[5] -- p[3];
    draw p[3] -- p[4];
    draw p[4] -- p[8];
    draw p[8] -- p[9];
    draw p[9] -- p[6];
    draw p[6] -- p[7];
    draw p[0] -- p[2];
    draw p[2] -- p[8];
    draw p[6] -- p[1];
    draw p[1] -- p[3];
    draw p[1] -- p[2];
    draw thelabel(textext("$s_1$"), (0,0)) scaled 0.2u shifted (p[4] + (p[4] - O) * 0.35);
    draw thelabel(textext("$t_1$"), (0,0)) scaled 0.2u shifted (p[7] + (p[7] - O) * 0.35);
    draw thelabel(textext("$s_2$"), (0,0)) scaled 0.2u shifted (p[5] + (p[5] - O) * 0.35);
    draw thelabel(textext("$t_2$"), (0,0)) scaled 0.2u shifted (p[9] + (p[9] - O) * 0.35);

    for i = 0 upto 9:
        fill fullcircle scaled r shifted p[i] withcolor white;
        draw fullcircle scaled r shifted p[i];
        draw thelabel(textext("$v_" & decimal i & "$"), (0,0)) scaled 0.2u shifted p[i];
    endfor;
endfig;

beginfig(3)
    u := 0.7cm;

    noderadius := 0.5u;
    node.x(textext("$x$"));
    node.a(textext("$a$"));
    node.b(textext("$b$"));
    node.c(textext("$c$"));
    node.d(textext("$d$"));
    node.y(textext("$y$"));
    node.zz(textext("$z$"));
    node.e(textext("$e$"));
    x.c = (5u, 0u);
    a.c = x.c + (-2u, 1.5u);
    b.c = x.c + (1u, 1.5u);
    c.c = a.c + (0, 3u);
    d.c = b.c + (-1u, 3u);
    y.c = c.c + (1u, 1.5u);
    zz.c = y.c + (3u, -2u);
    e.c = b.c + (2u, 0u);
    drawboxed(x, a, b, c, d, y, zz, e);
    draw arc(x)(--)(a);
    draw arc(x)(--)(b);
    draw arc(a)(--)(c);
    draw arc(a)(--)(d);
    draw arc(b)(--)(d);
    draw arc(c)(--)(y);
    draw arc(d)(--)(y);
    draw arc(d)(--)(zz);
    draw arc(x)(--)(e);
    draw arc(b)(--)(zz);
    draw arc(e)(--)(zz);
endfig;

beginfig(4)
    u := 1.5cm;
    node.s1(textext("$s_1$"));
    node.t1(textext("$s_2$"));
    node.s2(textext("$t_1$"));
    node.t2(textext("$t_2$"));
    node.x(textext("$x$"));
    s1.c = (2u, 5u);
    x.c = (2u, 4u);
    t1.c = (2u, 0u);
    s2.c = (0.5u, 2u);
    t2.c = (4u, 2u);
    drawboxed(s1, t1, s2, t2, x);
    draw arc(s1)(--)(x);
    draw arc(x)({(-10,-1)}..)(t1);
    draw arc(s2)({(1,1)}..{(1,1)})(t2);
endfig;
end.
