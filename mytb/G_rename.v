module top ( a , b , c , o1, o2 );
input a , b , c ;
output o1 , o2 ;
wire h1 , h2 , h3 , h4 , h5;

// buf ( h5, c );
not ( h1 , c );
and ( h2 , a , h1 );
nor ( h3 , a , b );
and ( h4 , b , c );
and ( o1 , b , h2 );
or ( o2 , h2 , h3 , h4 );

endmodule
