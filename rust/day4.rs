use std::fs;

fn part1(file_path: &str) -> i32 {
    let text = fs::read_to_string(file_path);
    let mut res = 0;
    match text {
        Ok(x) => {
            let s = x.to_owned();
            let lines = s.split('\n').collect::<Vec<&str>>();
            for line in lines {
                let nums = line.split(':')
                                .collect::<Vec<&str>>()[1]
                                .trim();
                let left_side = nums.split('|')
                                    .collect::<Vec<&str>>()[0]
                                    .split(' ')
                                    .collect::<Vec<&str>>();
                let right_side = nums.split('|')
                                    .collect::<Vec<&str>>()[1]
                                    .split(' ')
                                    .collect::<Vec<&str>>();
                
                let win_nums: Vec<_> = left_side.iter()
                                                .filter(|s| s.len() != 0)
                                                .map(|s| s.to_string().parse::<i32>().unwrap())
                                                .collect();
                let own_nums: Vec<_> = right_side.iter()
                                                .filter(|s| s.len() != 0)
                                                .map(|s| s.to_string().parse::<i32>().unwrap())
                                                .collect();

                let mut points = 0;

                for n in own_nums {
                    if win_nums.contains(&n) {
                        if points == 0 { points = 1; }
                        else { points = points * 2; }
                    }
                }

                res = res + points
            }
        },
        Err(_) => todo!()
    }
    res
}