require 'rake/clean'

CLEAN.include %w( in out test a.out *.class )
COMPILER_FOR = {"cpp" => "g++", "c" => "gcc", "java" => "javac" }
FLAGS_FOR = { "cpp" => "-lm -lcrypt -O2 -pipe -DONLINE_JUDGE",
              "c" => "-lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE",
}

desc "Build the latest modified problem solution"
task :build, :target do |t, args|
  begin
    target = args.target || Dir.glob("*").reject {|f| (f =~ /\.(c|cpp|java)$/).nil?}.max_by {|f| File.mtime(f)}
    puts "building #{target}"
    extension = target.split('.').last
    compiler = COMPILER_FOR[extension]
    flags = FLAGS_FOR[extension]
    sh "#{compiler} #{flags} #{target}"
  rescue
    fail "Nothing to build"
  end
end

task :default => :build
