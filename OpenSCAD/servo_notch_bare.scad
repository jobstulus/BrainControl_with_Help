
$fn=100;

translate([-1,-27.5,2.5]){
    rotate(a=[0,0,0])
    linear_extrude(height = 4, center = true, convexity = 10, twist = 0)
    polygon(points=[[0,0],[3,0],[0,5]], paths=[[0,1,2]]);
}

rotate([90,0,0]) union(){
    translate([-5,0,0.2]) cube([5,5,40]);
    difference(){
        translate([-2.5,5,-1.6]) rotate([90,90,0]) cylinder(5,5,5);
        translate([-2.5,5.3,-1.5]) rotate([90,90,0]) cylinder(5.5,1.7,1.7);
    }
}
translate([-16.5,1,0])  cube([12,3,5]);