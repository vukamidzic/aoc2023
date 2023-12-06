use std::fs;

fn part1(file_path: &str) -> i32 {
    let text = fs::read_to_string(file_path);
    match text {
        Ok(x) => {
            let s = x.to_owned();
            let lines = s.split('\n').collect::<Vec<&str>>();
            let fst_line = lines[0].split(':')
                                .collect::<Vec<&str>>()[1]
                                .trim()
                                .split_whitespace()
                                .collect::<Vec<&str>>();
            let snd_line = lines[1].split(':')
                                .collect::<Vec<&str>>()[1]
                                .trim()
                                .split_whitespace()
                                .collect::<Vec<&str>>();

            let times: Vec<_> = fst_line.iter().map(|n| n.parse::<i32>().unwrap()).collect();
            let records: Vec<_> = snd_line.iter().map(|n| n.parse::<i32>().unwrap()).collect();

            let mut result = 1;
            for i in 0..times.len() {
                let mut ways = 0;
                for j in 1..times[i] {
                    if j*(times[i]-j) > records[i] { ways = ways + 1;}
                } 
                result = result * ways;
            }

            result
        },
        Err(_) => todo!()
    }
}

fn part2(file_path: &str) -> i64 {
    let text = fs::read_to_string(file_path);
    match text {
        Ok(x) => {
            let s = x.to_owned();
            let lines = s.split('\n').collect::<Vec<&str>>();

            let time = lines[0].split(':')
                                .collect::<Vec<&str>>()[1]
                                .trim()
                                .split_whitespace()
                                .collect::<Vec<&str>>()
                                .join("")
                                .parse::<i64>()
                                .unwrap();

            let record = lines[1].split(':')
                                .collect::<Vec<&str>>()[1]
                                .trim()
                                .split_whitespace()
                                .collect::<Vec<&str>>()
                                .join("")
                                .parse::<i64>()
                                .unwrap();

            let (mut l, mut r) = (1, time-1);
            
            while l < time {
                if l*(time-l) <= record {l = l+1;}
                else {break;}
            }
            while r > 0 {
                if r*(time-r) <= record {r = r-1;}
                else {break;}
            }
            
            r-l+1
        },
        Err(_) => todo!()
    }
}