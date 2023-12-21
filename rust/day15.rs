use std::fs;
use std::collections::HashMap;

fn hash17(s: &str) -> u32 {
    s.chars()
        .collect::<Vec<_>>()
        .iter()
        .fold(0, |acc, c| ((acc + *c as u32) * 17) % 256)
} 

fn part1(file_path: &str) -> u32 {
    let text = fs::read_to_string(file_path);

    match text {
        Ok(x) => {
            let lines: Vec<_> = x.lines().filter(|s| s.len() != 0).collect();
            let mut result: u32 = 0;
            for line in lines {
                result += line.split(',')
                    .collect::<Vec<_>>()
                    .iter()
                    .map(|s| hash17(s))
                    .collect::<Vec<_>>()
                    .iter()
                    .sum::<u32>()
            }
            result
        },
        Err(_) => todo!()
    }
}

fn map_f(box_num: u32, lenses: Vec<(String, u32)>) -> u32 {
    let mut result: u32 = 0;
    for i in 0..lenses.len() {
        result += (box_num + 1) * ((i + 1) as u32) * lenses[i].1; 
    }
    result
}

fn part2(file_path: &str) -> u32 {
    let text = fs::read_to_string(file_path);

    match text {
        Ok(x) => {
            let lines: Vec<_> = x.lines().filter(|s| s.len() != 0).collect();
            let mut result: u32 = 0;
            let mut mp: HashMap<u32, Vec<(String, u32)>> = HashMap::new();
            for line in lines {
                for cmd in line.split(',').collect::<Vec<_>>() {
                    if cmd.chars().nth(cmd.len()-1).unwrap() == '-' {  
                        let lens_name: String = cmd.split('-').collect::<Vec<_>>()[0].to_string();
                        let lens_hash = hash17(&lens_name.to_owned());
                        if let Some(x) = mp.get_mut(&lens_hash) {
                            x.retain(|(name, _)| *name != lens_name);
                            if x.len() == 0 { mp.remove(&lens_hash); }
                        }
                    } 
                    else { 
                        let info = cmd.split('=').collect::<Vec<_>>();
                        let (lens_name, length) = (info[0], info[1]);
                        let lens_hash = hash17(&lens_name);
                        if mp.get(&lens_hash).is_none() {
                            mp.insert(lens_hash, vec![(lens_name.to_string(), length.parse::<u32>().unwrap())]);
                        }
                        else if let Some(x) = mp.get_mut(&lens_hash) {
                            let mut i: usize = 0;
                            for elem in &mut *x {
                                if elem.0 == lens_name { break; }
                                i += 1;
                            }

                            if i == x.len() { x.push((lens_name.to_string(), length.parse::<u32>().unwrap())); }
                            else { x[i].1 = length.parse::<u32>().unwrap(); }
                        }
                    }
                } 
            }

            for (k, v) in mp {
                result += map_f(k, v);
            }
            result
        },
        Err(_) => todo!()
    }
}

fn main() {
    println!("{}", part2("input.txt"));
}