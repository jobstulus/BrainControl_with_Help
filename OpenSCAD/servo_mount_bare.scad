$fn=100;

translate([0,0,3]){
    rotate([90,0,0]){
    difference(){
        translate([-15,-3,0]) cube([60.5,23,3.5]);
        translate([5,12,1]) cylinder(8,1.7,1.7,true);
        translate([20,12,1]) cylinder(8,1.7,1.7,true);
        /********************************************/
        translate([-18,8.5,3]) cylinder(10,8.5,8.5,true);
        translate([-9,0,1]) cylinder(8,1.2,1.2,true);
        translate([-9,17,1]) cylinder(8,1.2,1.2,true);
    }


    difference(){
        translate([0,0,0]) rotate([90,0,0]) cube([45.5,16.8,3]);
        translate([12,0,0]){
            translate([4.5,-4,5]) cube([23.6,10,12]);
            translate([2.5,0,11]) 
                rotate([90,0,0]) cylinder(8,1.3,1.4,true);
            translate([30.5,0,11]) 
                rotate([90,0,0]) cylinder(8,1.3,1.4,true);
        }

    }
    }

    translate([39.5,0,-3]) cube([6,5,23]);
    translate([-7,0,-3]) cube([6,5,23]);    
}

