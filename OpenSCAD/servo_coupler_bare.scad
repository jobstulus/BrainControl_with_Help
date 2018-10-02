$fn=100;


rotate([180,0,0])translate([0,0,-3])
difference(){
    hull(){
        cylinder(6,12.15/2,12.15/2,true);
        translate([0,2,0])cylinder(6,12.15/2,12.15/2,true);
        translate([45.5,0,0]) cylinder(6,8.13/2,8.13/2,true);
        translate([45.5,2,0]) cylinder(6,8.13/2,8.13/2,true);   
        translate([0,0,-3])   
        hull(){
            cylinder(6,12.15/2,12.15/2,true);
            translate([0,2,0])cylinder(6,12.15/2,12.15/2,true);
            translate([45.5,0,0]) cylinder(6,8.13/2,8.13/2,true);
            translate([45.5,2,0]) cylinder(6,8.13/2,8.13/2,true);   
        }
    } 

    cylinder(10,1.2,1.2,true);
    translate([0,0,-9]) cylinder(15,3,3,true);

    translate([0,0,2]){
        hull(){
            cylinder(3,7.45/2,7.45/2,true);
            translate([18.5,0,0]) cylinder(3,4.43/2,4.43/2,true);
        } 
    }
    translate([40,0,0]) cylinder(16,1.8,1.8,true);
    translate([-14,-9,-8])rotate([0,0,-2.5])cube([80,15,5]);
}

 