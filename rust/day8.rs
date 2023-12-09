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

fn main() {
    println!("{}", part1("input.txt"));
}