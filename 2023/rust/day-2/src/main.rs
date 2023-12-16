use std::collections::HashMap;
use std::fs;
use std::io::Result;

fn main() {
    part_1();
    part_2();
}

fn part_1() {
    let game: HashMap<&str, u32> = HashMap::from(
        [
            ("red", 12),
            ("green", 13),
            ("blue", 14)
        ]
    );
    let mut id_sum: u32 = 0;
    let input_result: Result<String> = fs::read_to_string("input");

    if input_result.is_err() {
        panic!("Could not find input file for day 2.")
    }

    let input: String = input_result.unwrap();
    // Get rid of all spaces, and the beginning of the line(Game %d: )
    let lines: Vec<String> = input.lines().map(
        |line| line.split("Game ")
            .filter(|x| *x != "Game")
            .collect()
    ).collect();

    for line in lines {
        let id_plus_line: Vec<&str> = line.split(": ").collect();
        let id: u32 = id_plus_line[0].parse::<u32>().unwrap();
        let rest_of_line: String = String::from(id_plus_line[1]);

        let sets: Vec<&str> = rest_of_line.split(";").collect();

        let mut is_set_valid: bool = true;
        for set in sets {
            let colors: Vec<&str> = set.split(",").filter_map(|x| Option::from(x.trim())).collect();
            for color in &colors {
                let color_count_plus_type: Vec<&str> = color.split(" ").collect();
                let count: u32 = color_count_plus_type.get(0).unwrap().parse().unwrap();
                let color: &&str = color_count_plus_type.get(1).unwrap();

                if count > *game.get(color).unwrap_or(&0u32) {
                    is_set_valid = false;
                    break;
                }
            }
        }

        if is_set_valid {
            id_sum += id;
        }
    }
    println!("Part 1 ID Sum: {}", id_sum);
}

fn part_2() {

}