use std::io;

fn input() -> (Vec<Vec<i32>>, Vec<Vec<i32>>, usize, usize) {

    println!("행렬의 크기를 입력해라: ");
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let input: Vec<&str> = input.trim().split_whitespace().collect();

    let a: usize = input[0].trim().parse().unwrap();
    let b: usize = input[1].trim().parse().unwrap();

    println!("첫번째 행렬을 입력해라: ");
    let mut first : Vec<Vec<i32>> = Vec::new();
    for _i in 0..a {
        let mut line = String::new();
        io::stdin().read_line(&mut line).unwrap();

        let mut matrix: Vec<i32> = Vec::new();

        let parts = line.trim().split_whitespace();
        for part in parts {
            let num: i32 = part.parse().unwrap();
            matrix.push(num);
        }
        first.push(matrix);
    }

 println!("두번째 행렬을 입력해라: ");
    let mut second : Vec<Vec<i32>> = Vec::new();
    for _j in 0..a {
        let mut line = String::new();
        io::stdin().read_line(&mut line).unwrap();

        let mut matrix: Vec<i32> = Vec::new();

        let parts = line.trim().split_whitespace();
        for part in parts {
            let num: i32 = part.parse().unwrap();
            matrix.push(num);
        }
        second.push(matrix);
    }

    (first, second, a, b)
}

fn result(first: Vec<Vec<i32>>, second: Vec<Vec<i32>>, a: usize, b: usize){

    if a!=b {
        println!("행렬의 크기가 맞지 않다.");
        return;
    }


    let mut result: Vec<Vec<i32>> = vec![vec![0; b]; a];

    println!("행렬의 덧셈 결과 : ");
    for i in 0..a {
        for j in 0..b {
            result[i][j] = first[i][j] + second[i][j];
            print!("{} ", result[i][j]);
        }
        println!();
    }

}

fn main(){

    let (first, second, a, b) = input();
    result(first, second, a, b);

}
