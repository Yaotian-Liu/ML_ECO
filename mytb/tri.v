module top (
    a, b, c, d, out
);
    input a, b, c, d, e, f, g, h;
    output out;

    wire g1, g2, g3, g4, g5, g6;
    and (g1, a, b);
    and (g2, c, d);
    and (g3, e, f);
    and (g4, g, h);
    
    and (g5, g1, g2);
    and (g6, g3, g4);

    assign out = g5 & g6;

endmodule