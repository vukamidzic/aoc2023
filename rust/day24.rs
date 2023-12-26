use std::fs;

const BOTTOM: i128 = 200000000000000;
const TOP: i128 = 400000000000000;

#[derive(Debug)]
struct Vector {
    x: i128,
    y: i128,
}

impl Vector {
    fn new(x: i128, y: i128) -> Vector {
        Vector {x, y}
    }
}

fn part1(file_path: &str) -> i32 { 
    let mut points: Vec<(Vector, Vector)> = vec![];

    if let Ok(x) = fs::read_to_string(file_path) {
        let lines = x.lines().collect::<Vec<_>>();
        for line in lines {
            let info = line.split('@').collect::<Vec<_>>();
            let (str_point, str_dir) = (
                info[0].trim().split(",").collect::<Vec<_>>(), 
                info[1].trim().split(",").collect::<Vec<_>>()
            );
            let (point, dir) = (
                &str_point[0..2].into_iter().map(|s| s.trim().parse::<i128>().unwrap()).collect::<Vec<_>>(), 
                &str_dir[0..2].into_iter().map(|s| s.trim().parse::<i128>().unwrap()).collect::<Vec<_>>()
            );
            points.push((Vector::new(point[0], point[1]), Vector::new(dir[0], dir[1])));
        }
    }

    let mut counter = 0;
    for i in 0..points.len() {
        for j in i+1..points.len() {
            let (v1, d1) = &points[i];
            let (v2, d2) = &points[j];

            let (a1, b1, c1) = (d1.y, -d1.x, d1.y*v1.x - d1.x*v1.y);
            let (a2, b2, c2) = (d2.y, -d2.x, d2.y*v2.x - d2.x*v2.y);

            if a1*b2 != a2*b1 {
                let (res_x, res_y) = (
                    (c1*b2 - c2*b1)/(a1*b2-a2*b1),
                    (c1*a2 - c2*a1)/(b1*a2-b2*a1)
                );

                if (res_x-v1.x)*d1.x >= 0 && (res_y-v1.y)*d1.y >= 0 &&
                (res_x-v2.x)*d2.x >= 0 && (res_y-v2.y)*d2.y >= 0 { 
                    if res_x >= BOTTOM && res_x <= TOP && 
                        res_y >= BOTTOM && res_y <= TOP {
                        counter += 1; 
                    }
                }
            }
        }
    }
    counter
}