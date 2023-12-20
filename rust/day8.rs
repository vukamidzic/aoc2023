use std::fs;
use std::collections::HashMap;

fn part1(file_path: &str) -> i32 {
    let text = fs::read_to_string(file_path);
    match text {
        Ok(x) => {
            let lines: Vec<_> = x.lines().filter(|s| s.len() != 0).collect();
            let moves: Vec<_> = lines[0].chars().collect();
            let info: HashMap<_, _> = lines[1..].to_vec()
                                        .iter()
                                        .map(|s| {
                                            let tmp = s.split("=").collect::<Vec<_>>();
                                            (
                                                tmp[0].trim(), 
                                                tmp[1].trim()
                                                        .split(", ")
                                                        .collect::<Vec<_>>()
                                                        .iter()
                                                        .map(|ss| ss.trim_start_matches('(')
                                                                    .trim_end_matches(')')
                                                            )
                                                        .collect::<Vec<_>>()
                                            )
                                        })
                                        .collect();
            
            let mut num_moves = 0;
            let mut start_str: &str = "AAA";
            let mut cnt: usize = 0;

            while start_str != "ZZZ" {
                match moves[cnt] {
                    'L' => {
                        match info.get(start_str) {
                            Some(pair) => {start_str = pair[0];},
                            None => todo!()
                        }
                    },
                    'R' => {
                        match info.get(start_str) {
                            Some(pair) => {start_str = pair[1];},
                            None => todo!()
                        }
                    },
                    _ => todo!()
                }
                cnt = (cnt + 1) % moves.len();
                num_moves = num_moves + 1;
            }

            num_moves
        },
        Err(_) => todo!()
    }
}

fn path_len<'a>(moves: &Vec<char>, s: &'a str, info: &HashMap<&str, Vec<&'a str>>) -> i32 {
    let mut tmp = s;
    let mut cnt: usize = 0;
    let mut num_moves = 0;

    while !tmp.ends_with("Z") {
        match moves[cnt] {
            'L' => {
                match info.get(&tmp as &str) {
                    Some(pair) => {tmp = pair[0];},
                    None => todo!()
                }
            },
            'R' => {
                match info.get(&tmp as &str) {
                    Some(pair) => {tmp = pair[1];},
                    None => todo!()
                }
            },
            _ => todo!()
        }

        num_moves = num_moves + 1;
        cnt = (cnt + 1) % moves.len();   
    }

    num_moves
}

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 { a as i64 }
    else { gcd(b, a % b) as i64}
}

fn part2(file_path: &str) -> i64 {
    let text = fs::read_to_string(file_path);
    match text {
        Ok(x) => {
            let lines: Vec<_> = x.lines().filter(|s| s.len() != 0).collect();
            let moves: Vec<_> = lines[0].chars().collect();
            let info: HashMap<_, _> = lines[1..].to_vec()
                                        .iter()
                                        .map(|s| {
                                            let tmp = s.split("=").collect::<Vec<_>>();
                                            (
                                                tmp[0].trim(), 
                                                tmp[1].trim()
                                                        .split(", ")
                                                        .collect::<Vec<_>>()
                                                        .iter()
                                                        .map(|ss| ss.trim_start_matches('(')
                                                                    .trim_end_matches(')')
                                                            )
                                                        .collect::<Vec<_>>()
                                            )
                                        })
                                        .collect();
            
            let keys: Vec<_> = info.keys().map(|s| *s).collect::<Vec<_>>();
            let start_strs: Vec<_> = keys.iter()
                                                .filter(|s| s.ends_with("A"))
                                                .collect::<Vec<_>>();

            let result: i64 = start_strs.iter()
                                    .map(|s| path_len(&moves, s, &info))
                                    .fold(1, |acc, x| (acc*(x as i64))/gcd(acc, (x as i64)));
            result
        },
        Err(_) => todo!()
    }
}