"""CLI for local testing of solutions in Distributed Code Jam."""
import argparse
import os
import subprocess
import sys

from dcj import build
from dcj import command_chooser
from dcj import configuration
from dcj import run
from dcj import test


def _print(x):
  print ' '.join(x)
  return 0  # Tell tool that command execution was succesfull.


if __name__ == '__main__':
  parser = argparse.ArgumentParser(prog='dcj')
  config = configuration.Configuration()
  # TODO(jbartosik): allow using different configs.
  config.Load(
      os.path.join(os.path.dirname(os.path.realpath(__file__)), 'config.json'))
  builder = build.Build(config)
  runner = run.Run(config)
  tester = test.Tester(builder, runner)
  chooser = command_chooser.CommandChooser({
      'build': builder,
      'run': runner,
      'test': tester,
  })
  chooser.AddToParser(parser)
  parser.add_argument(
      '--dry-run',
      action='store_true',
      help='Only print commands, don\'t execute them.',
      default=False)
  args = parser.parse_args()

  if args.dry_run:
    builder.SetCommandExecutor(_print)
    runner.SetCommandExecutor(_print)
  else:
    builder.SetCommandExecutor(subprocess.call)
    runner.SetCommandExecutor(subprocess.call)

  try:
    chooser.Run(args)
  except (NotImplementedError, RuntimeError, ValueError) as error:
    print error
    sys.exit(1)
