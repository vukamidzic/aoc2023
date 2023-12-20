use std::fs;

fn hash17(s: &str) -> u32 {
    s.chars()
        .collect::<Vec<_>>()
        .iter()
        .fold(0, |acc, c| ((acc + *c as u32) * 17) % 256)
} 

fn part1(file_path: &str) {
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
            println!("{result}");
        },
        Err(_) => todo!()
    }
}