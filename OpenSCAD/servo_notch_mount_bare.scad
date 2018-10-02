$fn=100;


translate([57,6,10.5]){
    difference(){
        union(){
            translate([-57,-6,-10.5]) cube([16,14,10]);
            translate([-57,8,-2]) rotate([90,0,0]) cube([12,5,14]);
        }
        translate([-57.1,-2,-7]) cube([13.2,6,14]);
        translate([-52,11,-1]) rotate([90,0,0]) cylinder(20,1.7,1.7);
        translate([-45,1,-4])rotate([0,90,0]) cylinder(10,1.6,1.6,true);
    }
}

