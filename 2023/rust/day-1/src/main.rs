use std::collections::HashMap;
use std::fs;
use std::io::Result;

fn main() {
    part_1();
    part_2();
}

fn part_1() {
    let mut sum: u32 = 0;
    let input_result: Result<String> = fs::read_to_string("input");

    if input_result.is_err() {
        panic!("Could not find input file for day 1.")
    }

    let input: String = input_result.unwrap();

    for line in input.lines() {
        let mut numbers = line.chars().filter_map(|c| c.to_digit(10));
        let first_number: u32 = numbers.next().unwrap();
        let last_number: u32 = numbers.last().unwrap_or(first_number);

        let final_number: u32 = first_number * 10 + last_number;
        sum += final_number;
    }

    println!("Part 1 Sum: {}", sum);
}

fn part_2() {
    let number_words: HashMap<&str, u32> = HashMap::from([
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9)
    ]);
    let mut sum: u32 = 0;
    let input_result: Result<String> = fs::read_to_string("input");

    if input_result.is_err() {
        panic!("Could not find input file for day 1.")
    }

    let input: String = input_result.unwrap();

    let sum: u32 = input.lines().map(|line| {
        let line = line.chars().collect::<Vec<_>>();
        let mut i = 0;
        let mut list = Vec::new();
        'iterate_chars: while i < line.len() {
            if line[i].is_digit(10) {
                list.push(line[i].to_digit(10).unwrap());
            } else {
                for word in &number_words {
                    if line[i..].starts_with(&word.0.chars().collect::<Vec<_>>()[..]) {
                        list.push(*word.1);
                        i += word.0.len() - 1;
                        continue 'iterate_chars;
                    }
                }
            }
            i += 1;
        }
        (list.first().unwrap() * 10) + list.last().unwrap()
    }).sum::<u32>();
    println!("Part 2 Sum: {}", sum);
}
